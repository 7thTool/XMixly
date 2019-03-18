var $builtinmodule = function (name) {
    var mod = {
        data: {
            temperature: mbData['temperature'],
            distance : mbData['distance'],
            distance_infrared_left : mbData['distance_infrared_left'],
            distance_infrared_right : mbData['distance_infrared_right'],
            brightness: mbData['brightness'],
            soundlevel: mbData['soundlevel'],
        }
    };

    mod.panic = new Sk.builtin.func(function(n) {
        ui.output("Panic mode: " + n.v);
    });

    var start_time = Date.now();
    mod.reset = new Sk.builtin.func(function() {
        start_time = Date.now();
        // not implemented yet
    });

    mod.running_time = new Sk.builtin.func(function() {
        return Sk.builtin.int_(Date.now() - start_time);
    });

    var ioPinDigital = new Sk.misceval.buildClass(mod, function($gbl, $loc) {
        $loc.__init__ = new Sk.builtin.func(function(self, name) {
            self.name = name.v;
            self.value = 0;
        });

        $loc.read_digital = new Sk.builtin.func(function(self){
            $('select.pinOption').each(function(){
                if($(this).val() == self.name){
                    var id = $(this).attr('id').split('select_row').join('');
                    self.value = parseInt($('#curr_pinValue'+id).text());
                }
            });
            return Sk.builtin.int_(self.value);
        });

        $loc.write_digital = new Sk.builtin.func(function(self, value){
            self.value = value.v == 1? 1: 0;
            ui.updateMicrobitPins('digital',self.name,self.value);
        });
    }, "MicroBitDigitalPin", []);

    mod.pin5 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(5));
    mod.pin6 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(6));
    mod.pin7 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(7));
    mod.pin8 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(8));
    mod.pin9 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(9));
    mod.pin11 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(11));
    mod.pin12 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(12));
    mod.pin13 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(13));
    mod.pin14 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(14));
    mod.pin15 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(15));
    mod.pin16 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(16));
    mod.pin19 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(19));
    mod.pin20 = Sk.misceval.callsim(ioPinDigital, Sk.builtin.int_(20));

    var ioPinAnalog = new Sk.misceval.buildClass(mod, function($gbl, $loc) {
        $loc.__init__ = new Sk.builtin.func(function(self,name) {
            self.value = 0;
            self.name = name.v
            self.period_us = 35;
        });

        $loc.read_analog = new Sk.builtin.func(function(self) {
            var flag = false;//是否能够找到该列
            $('select.pinOption').each(function(){
                if($(this).val()==self.name){
                    flag = true;
                    var id = $(this).attr('id').split('select_row').join('');
                    self.value = parseInt($('#curr_pinValue'+id).text());
                }
            });
            if(!flag){//找不到就新建一个
                ui.updateMicrobitPins('analog',self.name,self.value);
            }
            return Sk.builtin.int_(self.value);

        });

        $loc.write_analog = new Sk.builtin.func(function(self, value) {
            self.value = value.v;
            ui.updateMicrobitPins('analog',self.name,self.value);
        });

        $loc.set_analog_period = new Sk.builtin.func(function(self, period) {
            self.period_us = period.v * 1000;
            ui.updateUIAnalogPeriod(self.name,self.period_us);
        });

        $loc.set_analog_period_microseconds = new Sk.builtin.func(function(self, period) {
            self.period_us = period.v;
            ui.updateUIAnalogPeriod(self.name,self.period_us);
        });

    }, "MicroBitAnalogPin", []);
    mod.pin3 = Sk.misceval.callsim(ioPinAnalog, Sk.builtin.int_(3));
    mod.pin4 = Sk.misceval.callsim(ioPinAnalog, Sk.builtin.int_(4));
    mod.pin10 = Sk.misceval.callsim(ioPinAnalog, Sk.builtin.int_(10));

    var ioPinTouch = new Sk.misceval.buildClass(mod, function($gbl, $loc) {
        $loc.__init__ = new Sk.builtin.func(function(self,name) {
            self.name = name.v;
            self.touched = false;
        });

        $loc.is_touched = new Sk.builtin.func(function(self) {
            $('select.pinOption').each(function(){
                if($(this).val()==self.name){
                    flag = true;
                    var id = $(this).attr('id').split('select_row').join('');
                    self.touched = parseInt($('#curr_pinValue'+id).text()) === 1 ? true : false;
                }
            });
            return Sk.builtin.bool(self.touched);
        });
    }, "MicroBitTouchPin", []);

    mod.pin0 = Sk.misceval.callsim(ioPinTouch, Sk.builtin.int_(0));
    mod.pin1 = Sk.misceval.callsim(ioPinTouch, Sk.builtin.int_(1));
    mod.pin2 = Sk.misceval.callsim(ioPinTouch, Sk.builtin.int_(2));
    ui.bindAddPinBtnEvent('digital');
    ui.bindAddPinBtnEvent('analog');
    ui.bindAddPinBtnEvent('touch');

    mod.Button = new Sk.misceval.buildClass(mod, function($gbl, $loc) {
        $loc.__init__ = new Sk.builtin.func(function(self) {
            self.presses = 0;
            self.pressed = false;
            self.last_checked = 0;
        });

        $loc.is_pressed = new Sk.builtin.func(function(self) {
            return Sk.builtin.bool(self.pressed);
        });

        $loc.was_pressed = new Sk.builtin.func(function(self) {
            var r = self.presses > self.last_checked;
            self.last_checked = self.presses;
            return Sk.builtin.bool(r);
        });

        $loc.get_presses = new Sk.builtin.func(function(self) {
            var presses = self.presses;
            self.presses = 0;
            return Sk.builtin.int_(presses);
        });
    }, "Button", []);

    mod.button_a = new mod.Button();
    mod.button_b = new mod.Button();
    ui.bindBtnEvent('btn_A', [mod.button_a]);
    ui.bindBtnEvent('mixgo_btn_A', [mod.button_a]);
    ui.bindBtnEvent('btn_B', [mod.button_b]);
    ui.bindBtnEvent('mixgo_btn_B', [mod.button_b]);
    ui.bindBtnEvent('btn_both', [mod.button_a, mod.button_b]);

    mod.led = new Sk.misceval.buildClass(mod, function($gbl, $loc) {
        $loc.__init__ = new Sk.builtin.func(function(self, pin) {
            self.val = 1;
            self.pin = pin.v;
            self.brightness = 0;
            ui.addPinOption('analog', 5 * (self.pin - 1));
        });

        $loc.on = new Sk.builtin.func(function(self,n) {           
            self.val = 0;
        });

        $loc.off = new Sk.builtin.func(function(self) {
            self.val = 1;
        });

        $loc.setonoff = new Sk.builtin.func(function(pin, val) {
            if(val.v == -1){
                
            }
            else{
                
            }
            ui.setBoardLEDonoff(pin.v, 1 - self.val);
        });
        $loc.getonoff = new Sk.builtin.func(function() {
            return Sk.builtin.int_(1 - self.val);
        });
        var setbrightness = new Sk.builtin.func(function(self, pin, brightness) {
            ui.setBoardLEDbrightness(pin.v, brightness.v);
        });
        debugger;
        $loc.setbrightness = Sk.misceval.callsimOrSuspend(Sk.builtins.staticmethod, setbrightness);
    }, "led", []);

    led1 = Sk.misceval.callsim(led, Sk.builtin.int_(0));
    led2 = Sk.misceval.callsim(led, Sk.builtin.int_(5));

    mod.mixgo_get_soundlevel = new Sk.builtin.func(function(self) {
        return Sk.builtin.int_(mod.data.soundlevel);
    });
    ui.bindSliderEvent('soundsensor', mod.data, 'soundlevel');
    mod.mixgo_get_brightness = new Sk.builtin.func(function(self) {
        return Sk.builtin.int_(mod.data.brightness);
    });
    ui.bindSliderEvent('lightsensor', mod.data, 'brightness');

    mod.compass = new Sk.builtin.module();
    mod.compass.$d = new compass("mixgo.compass");

    mod.mpu = new Sk.builtin.module();
    mod.mpu.$d = new mpu("mixgo.mpu9250");

    mod.Infrared_left = new Sk.builtin.module();
    mod.Infrared_left.$d = new Infrared_left("mixgo.Infrared_left");
    mod.Infrared_right = new Sk.builtin.module();
    mod.Infrared_right.$d = new Infrared_right("mixgo.Infrared_right");

    /*
    mod.i2c = new Sk.builtin.module();
    mod.i2c.$d = new i2c("microbit.i2c");
    */

    mod.uart = new Sk.builtin.module();
    mod.uart.$d = new uart("microbit.uart");

    return mod;
}
