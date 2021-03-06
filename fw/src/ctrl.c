#include "ctrl.h"
#include "debug.h"
#include "timers.h"

ctrl_t _ctrl0;


ctrl_t* ctrl_default(){
        return &_ctrl0;
}


void ctrl_init(ctrl_t* ctrl){

        // debug init
        usart_init(usart_default(), DBG_USART_BAUD);
        debug_init(usart_default());

        //device i2c_init
        fb_init(fb_default());
        i2c_init(i2c_default());
        rtc_init(rtc_default(), i2c_default());
        dht_init(dht_default());
        view_init(view_default(), fb_default());

        key_init(key_default(), _ctrl_callback_on_key);
        lux_init(lux_default(), _ctrl_callback_on_lux);

        //read rtc and read setting
        view_data_t* view_data = &(view_default()->view_data);
        rtc_read(rtc_default(), &(view_data->rtc_date_time));
        setting_read(&view_data->setting_data);
        printf("ft:%d\n", view_data->setting_data.font_type);

        // create and start timers
        _ctrl_init_timers(ctrl);

        // it's show time!!!!
        view_show_chain(view_default(), _view_chain_default);

}

void _ctrl_init_timers(ctrl_t* ctrl){
        timer_new("key_scan", KEY_SCAN_PEROD_MS / portTICK_PERIOD_MS, _ctrl_timer_key_scan, true);
        timer_new("view_tick", VIEW_TICK_PEROD_MS / portTICK_PERIOD_MS, _ctrl_timer_view_tick, true);
        timer_new("read_lux", 150 / portTICK_PERIOD_MS,  _ctrl_timer_read_lux, true);
        timer_new("read_dht", 1000 / portTICK_PERIOD_MS, _ctrl_timer_read_dht, true);
        timer_new("read_rtc", 1000 / portTICK_PERIOD_MS, _ctrl_timer_read_rtc, true);
}

////////////////////////////////////////////////////////////////////////////////
void _ctrl_timer_key_scan(void* p){
        key_scan(key_default());
}

void _ctrl_timer_read_lux(void* p){
        lux_sample(lux_default());
}

void _ctrl_timer_read_rtc(void* p){
        view_data_t* view_data = &(view_default()->view_data);
        rtc_date_time_t* dt = &(view_data->rtc_date_time);
        if(view_data->ctrl_mode == CM_NORMAL) {
                result_t ret = rtc_read(rtc_default(), dt);
                //printf("h24:%d, pm=%d, h=%d\n", dt->h24, dt->pm, dt->hour);
                if(ret != ERR_OK) {
                        printf("read rtc error:%d\n", ret);
                        return;
                }
        }
}

void _ctrl_timer_view_tick(void* p){
        view_frame_tick(view_default());
}

void _ctrl_timer_read_dht(void* p){
        dht_data_t* dht_data = &(view_default()->view_data.dht_data);
        result_t ret = dht_read(dht_default(), dht_data);
        if(ret != ERR_OK) {
                printf("dht read error:%d\n", ret);
        }
        //printf("dht: %d %d\n", dht_data->humidity, dht_data->temperature);
}

void _ctrl_switch_mode(ctrl_t* ctrl, uint8_t ctrl_mode){
        printf("switch:%d\n", ctrl_mode);
        view_t* view = view_default();
        view_data_t* view_data = &(view->view_data);
        if(ctrl_mode != view_data->ctrl_mode) {
                view_data->ctrl_mode = ctrl_mode;
                if(ctrl_mode == CM_NORMAL) {
                        //TODO save setting
                        view_show_chain(view, _view_chain_default);
                }else{
                        view_data->set_field = SF_HOUR;
                        view_show_page(view,PG_TIME_SET);
                }
        }

}

////////////////////////////////////////////////////////////////////////////////

void _ctrl_callback_on_key(uint8_t key, uint8_t event){
        printf("key:%d,%d\n",key, event);
        view_t* view = view_default();
        ctrl_t* ctrl = ctrl_default();
        view_data_t * view_data = &(view_default()->view_data);
        if(key == KEY_2) {
                if( event == KEY_EVENT_KEYDOWN_LONG) {
                        //enter or leave setting mode
                        if(view_data->ctrl_mode == CM_NORMAL) {
                                _ctrl_switch_mode(ctrl, CM_SETTING);
                        }else{
                                _ctrl_switch_mode(ctrl, CM_NORMAL);
                        }
                }else if(event == KEY_EVENT_KEYDOWN) {
                        //enter setting mode
                        if(view_data->ctrl_mode == CM_SETTING) {
                                //next set field
                                if(view_data->set_field == SF_LUX) {
                                        //exit set mode
                                        _ctrl_switch_mode(ctrl, CM_NORMAL);
                                }else{
                                        //switch to next field
                                        view_data->set_field++;
                                        if(view_data->set_field == SF_MONTH) {
                                                view_show_page(view, PG_DATE_SET);
                                        }else if(view_data->set_field == SF_YEAR) {
                                                view_show_page(view, PG_YEAR_SET);
                                        }else if(view_data->set_field == SF_FONT) {
                                                view_show_page(view, PG_FONT_SET);
                                        }else if(view_data->set_field == SF_LUX){
                                                view_show_page(view, PG_LUX_SET);
                                        }
                                }
                        }
                }

        }


        if(key == KEY_1 && event == KEY_EVENT_KEYDOWN) {
                if(view_data->ctrl_mode == CM_SETTING) {
                        _ctrl_adjust_field_value(ctrl_default(), INCR);
                        _ctrl_apply_setting_value(ctrl_default());
                }else{
                      view_flip_next(view_default());
                }
        }

        if(key == KEY_3 && event == KEY_EVENT_KEYDOWN) {
                if(view_data->ctrl_mode == CM_SETTING) {
                        _ctrl_adjust_field_value(ctrl_default(), DECR);
                        _ctrl_apply_setting_value(ctrl_default());
                }
        }
}

void _ctrl_callback_on_lux(uint16_t lux){
        printf("lux: %d\n",lux);
        fb_t* fb = fb_default();
        setting_data_t* st = &(view_default()->view_data.setting_data);
        lux -= st->lux_adj * 50;
        if(lux < 100) {
                fb_set_brightness(fb, 7);
        }else if(lux < 150) {
                fb_set_brightness(fb, 6);
        }else if(lux < 200) {
                fb_set_brightness(fb, 5);
        }else if(lux < 250) {
                fb_set_brightness(fb, 4);
        }else if(lux < 300) {
                fb_set_brightness(fb, 3);
        }else if(lux < 350) {
                fb_set_brightness(fb, 2);
        }else if(lux < 400) {
                fb_set_brightness(fb, 1);
        }else{
                fb_set_brightness(fb, 0);
        }
}

// magic, haha
#define ADD_DELTA(ob, f, min, max, delta) {if(ob->f + delta == max + 1) {ob->f = min; }else if(ob->f + delta == min) {ob->f = max; }else{ ob->f+=delta; }}

void _ctrl_adjust_field_value(ctrl_t* ctrl, int8_t delta){
        view_data_t* view_data = &(view_default()->view_data);
        rtc_date_time_t* dt = &(view_data->rtc_date_time);
        setting_data_t* sd = &(view_data->setting_data);
        switch(view_data->set_field) {
        case SF_MINUTE: ADD_DELTA(dt, minute, 0, 59, delta); break;
        case SF_HOUR: ADD_DELTA(dt, hour, 0, 23, delta); break;
        case SF_DAY: ADD_DELTA(dt, day, 1, 31, delta); break;
        case SF_MONTH: ADD_DELTA(dt, month, 1, 12, delta); break;
        case SF_YEAR: ADD_DELTA(dt, year, 0, 99, delta); break;
        case SF_FONT: sd->font_type = !sd->font_type; break;
        case SF_LUX: ADD_DELTA(sd, lux_adj, -10, 10, delta); break;
        }
}


void _ctrl_apply_setting_value(ctrl_t* ctrl){
        view_data_t* view_data = &(view_default()->view_data);
        rtc_date_time_t* dt = &(view_data->rtc_date_time);
        setting_data_t* sd = &(view_data->setting_data);
        result_t ret;
        switch(view_data->set_field) {
        case SF_MINUTE:
        case SF_HOUR:
        case SF_DAY:
        case SF_MONTH:
        case SF_YEAR:
                ret = rtc_write(rtc_default(), dt);
                if(ret != ERR_OK) {
                        printf("rtc_write error:%d\n", ret);
                }
                break;
        case SF_FONT:
        case SF_LUX:

                setting_write(sd);
                break;
        }
}
