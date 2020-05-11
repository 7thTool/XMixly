'use strict';

goog.provide('Blockly.Arduino.xblockly');

goog.require('Blockly.Arduino');
goog.require('Blockly.JavaScript');

Blockly.Arduino.XBlockly_statementToCodeNoTab = function (block, name) {
  var code = Blockly.Arduino.statementToCode(block, name);
  if (Blockly.Arduino.STATEMENT_PREFIX) {
      var branch = Blockly.Arduino.prefixLines(
          Blockly.Arduino.STATEMENT_PREFIX.replace(/%1/g,
              '\'' + this.id + '\''), Blockly.Arduino.INDENT) + code;
  }
  if (Blockly.Arduino.INFINITE_LOOP_TRAP) {
      code = Blockly.Arduino.INFINITE_LOOP_TRAP.replace(/%1/g,
          '\'' + this.id + '\'') + code;
  }
  return code;
}

Blockly.Arduino.XBlockly_addInclude = function (tag,code) {
  Blockly.Arduino.definitions_['define_' + tag] = code;
}

Blockly.Arduino.XBlockly_addDeclaration = function (tag, code) {
  Blockly.Arduino.definitions_['var_' + tag] = code;
}

Blockly.Arduino.XBlockly_addFunction = function (tag, code) {
  Blockly.Arduino.definitions_[tag] = code;
}

Blockly.Arduino.XBlockly_addSetup = function (tag, code) {
  Blockly.Arduino.setups_['setup_' + tag] = code;
}

Blockly.Arduino.XBlockly_addGlobal = function () {
  //只要使用了xblockly，强制添加xblockly全局代码
  Blockly.Arduino.XBlockly_addInclude('Arduino', '#include <Arduino.h>');
  Blockly.Arduino.XBlockly_addInclude('PGKSystem', '#include <PGKSystem.h>');
  Blockly.Arduino.XBlockly_addSetup('PGKSystem', 'XSystem.setup();');
}

Blockly.Arduino.XBlockly_addOnBoardModule = function (type, label) {
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');
  var objName = label.toLowerCase();
  var globalCode = type + ' ' + objName + ';';
  Blockly.Arduino.XBlockly_addDeclaration(objName, globalCode);
  var setupCode = objName + '.setup(\"' + label + '\");';
  Blockly.Arduino.XBlockly_addSetup(objName, setupCode);
  //Blockly.Arduino.reservePort(label,objName);
}

Blockly.Arduino.XBlockly_isOnBoardModule = function (type, label) {
  if(type && label) {
      if(isNaN(label)) { //简单判断一下
          return true;
      }
  }
  return false;
}

Blockly.Arduino.XBlockly_getModuleName = function (type,port) {
  var name = "";
  var typeObj = window.XBlockly.getTypeObj(type);
  if (typeObj) {
      if (typeObj.type == 'XIODriver') {
          name = ('io_' + port).toLowerCase();
      } else {
          if (Blockly.Arduino.XBlockly_isOnBoardModule(typeObj.type, port)) {
              name = (port).toLowerCase();
          } else {
              if (typeObj.models && typeObj.models.length > 0) {
                  name = (typeObj.models[0].id.substring(0, 3) + '_' + port).toLowerCase();
              } else {
                  name = (port).toLowerCase();
              }
          }
      }
  }
return name;
}

//obj = [{type='',port=''}]
Blockly.Arduino.XBlockly_addService = function (type, n3c, objs) {
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');
  var objName = n3c;
  for(var i=0;i<objs.length;i++) {
      objName += '_' + Blockly.Arduino.XBlockly_getModuleName(objs[i].type, objs[i].port);
  }
  var globalCode = type + ' ' + objName + ';';
  Blockly.Arduino.XBlockly_addDeclaration(objName, globalCode);
  var setupCode = objName + '.setup(';
  for(var i=0;i<objs.length;i++) {
      setupCode += '&' + Blockly.Arduino.XBlockly_getModuleName(objs[i].type, objs[i].port);
  }
  setupCode += ');';
  Blockly.Arduino.XBlockly_addSetup(objName, setupCode);
  //var loopCode = objName + '.loop();';
  //Blockly.Arduino.addLoop(objName, loopCode, true);
}

Blockly.Arduino.XBlockly_getServiceName = function (type, n3c, objs) {
  var objName = n3c;
  for(var i=0;i<objs.length;i++) {
      objName += '_' + Blockly.Arduino.XBlockly_getModuleName(objs[i].type, objs[i].port);
  }
  return objName;
}


/********************************************
Construct - 连接模块
*********************************************/

Blockly.Arduino.xblockly_construct_INIT = function() {
  var main_board = this.getFieldValue('XMainBoard');
  if(window.XBlockly.MainBoard == main_board) {
    return '';
  }
  window.XBlockly.MainBoard = main_board;
  switch(main_board)
  {
    case 'PanGu': {
      var jsonObjects = '{"modules":[{"type":"XDualDCMotor","name":"双直流电机","models":[{"func":"####","type":"XRJ25","id":"DDM3300"}],"objects":[]},{"type":"XBuzzer","name":"蜂鸣器","models":[{"func":"D###","type":"XRJ25","id":"BUZ3300"}],"objects":[]},{"type":"XButton","name":"按钮","models":[{"func":"A###","type":"XRJ25","id":"BTN3300"}],"objects":[]},{"type":"XLightSensor","name":"光线传感器","models":[{"func":"A###","type":"XRJ25","id":"LIG3300"}],"objects":[]},{"type":"XSoundSensor","name":"声音传感器","models":[{"func":"A###","type":"XRJ25","id":"SND3300"}],"objects":[]},{"type":"XIRReceiver","name":"红外接收器","models":[{"func":"H###","type":"XRJ25","id":"IRR3300"}],"objects":[]},{"type":"XIRTracking","name":"红外循迹传感器","models":[{"func":"H###","type":"XRJ25","id":"IRT3320"}],"objects":[]},{"type":"XIRTracking6","name":"六路红外循迹传感器","models":[{"func":"####","type":"XRJ25","id":"IRT3360"}],"objects":[]},{"type":"XUltrasonic","name":"超声波传感器","models":[{"func":"H###","type":"XRJ25","id":"ULS3600"}],"objects":[]},{"type":"XSegDisplay","name":"数码管","models":[{"func":"H###","type":"XRJ25","id":"SGD4300"}],"objects":[]},{"type":"XLEDMatrix","name":"LED面板","models":[{"func":"####","type":"XRJ25","id":"LMT3300"}],"objects":[]},{"type":"XVoiceBroadcast","name":"语音播报器","models":[{"func":"####","type":"XRJ25","id":"VBC3300"}],"objects":[]},{"type":"XIRAvoiding","name":"红外避障传感器","models":[{"func":"H###","type":"XRJ25","id":"IRA3300"}],"objects":[]},{"type":"XPotentiometer","name":"电位器","models":[{"func":"A###","type":"XRJ25","id":"PTM3300"}],"objects":[]},{"type":"XRGBLed","name":"RGB彩灯","models":[{"func":"D###","type":"XRJ25","id":"RGB3340"}],"objects":[]},{"type":"XHumiture","name":"温湿度传感器","models":[{"func":"D###","type":"XRJ25","id":"HUM3300"}],"objects":[]},{"type":"XPIR","name":"人体红外传感器","models":[{"func":"D###","type":"XRJ25","id":"PIR3300"}],"objects":[]},{"type":"XShockSensor","name":"震动传感器","models":[{"func":"D###","type":"XRJ25","id":"SKS3300"}],"objects":[]},{"type":"XBluetooth","name":"蓝牙","models":[{"func":"U###","type":"XIP45","id":"BLT4140"}],"objects":[]},{"type":"XServo","name":"","models":[],"objects":[{"id":"SVO1","model":"SVO3000","name":"板载-SVO1"},{"id":"SVO2","model":"SVO3000","name":"板载-SVO2"}]},{"name":"端口","type":"XPORTS","models":[{"name":"端口 1","id":"1","type":"XRJ25","func":"DHP#"},{"name":"端口 2","id":"2","type":"XRJ25","func":"DHAK"},{"name":"端口 3","id":"3","type":"XRJ25","func":"DHP#"},{"name":"端口 4","id":"4","type":"XRJ25","func":"DHP#"},{"name":"端口 5","id":"5","type":"XRJ25","func":"DHPR"},{"name":"端口 6","id":"6","type":"XRJ25","func":"DHA#"},{"name":"端口 7","id":"7","type":"XRJ25","func":"DHA#"},{"name":"端口 8","id":"8","type":"XRJ25","func":"DHP#"},{"name":"端口 9","id":"9","type":"XIP45","func":"U###"}]}]}';
      window.XBlockly.init(JSON.parse(jsonObjects));
      Blockly.Arduino.XBlockly_addInclude('Arduino', '#include <Arduino.h>');
      Blockly.Arduino.XBlockly_addInclude('PGKSystem', '#include <PGKSystem.h>');
      Blockly.Arduino.XBlockly_addSetup('PGKSystem', 'XSystem.setup();');
    }
    break;
    case 'WuKong': {
      var jsonObjects = '{"modules":[{"type":"XIRTracking","name":"红外循迹传感器","models":[{"func":"H###","type":"XRJ25","id":"IRT3320"}],"objects":[]},{"type":"XIRTracking6","name":"六路红外循迹传感器","models":[{"func":"####","type":"XRJ25","id":"IRT3360"}],"objects":[]},{"type":"XUltrasonic","name":"超声波传感器","models":[{"func":"H###","type":"XRJ25","id":"ULS3600"}],"objects":[]},{"type":"XSegDisplay","name":"数码管","models":[{"func":"H###","type":"XRJ25","id":"SGD4300"}],"objects":[]},{"type":"XLEDMatrix","name":"LED面板","models":[{"func":"####","type":"XRJ25","id":"LMT3300"}],"objects":[]},{"type":"XVoiceBroadcast","name":"语音播报器","models":[{"func":"####","type":"XRJ25","id":"VBC3300"}],"objects":[]},{"type":"XIRAvoiding","name":"红外避障传感器","models":[{"func":"H###","type":"XRJ25","id":"IRA3300"}],"objects":[]},{"type":"XPotentiometer","name":"电位器","models":[{"func":"A###","type":"XRJ25","id":"PTM3300"}],"objects":[]},{"type":"XButton","name":"按钮","models":[{"func":"A###","type":"XRJ25","id":"BTN3300"}],"objects":[{"id":"BTN","model":"BTN3000","name":"板载-BTN"}]},{"type":"XBluetooth","name":"蓝牙","models":[{"func":"U###","type":"XIP45","id":"BLT4140"}],"objects":[]},{"type":"XSoundSensor","name":"","models":[],"objects":[{"id":"SND","model":"SND3000","name":"板载-SND"}]},{"type":"XLightSensor","name":"","models":[],"objects":[{"id":"LIG","model":"LIG4000","name":"板载-LIG"}]},{"type":"XBuzzer","name":"","models":[],"objects":[{"id":"BUZ","model":"BUZ4000","name":"板载-BUZ"}]},{"type":"XRGBLed","name":"","models":[],"objects":[{"id":"RGB","model":"RGB3060","name":"板载-RGB"}]},{"type":"XIRReceiver","name":"","models":[],"objects":[{"id":"IRR","model":"IRR3000","name":"板载-IRR"}]},{"type":"XDualDCMotor","name":"","models":[],"objects":[{"id":"DDM","model":"DDM3001","name":"板载-DDM"}]},{"type":"XServo","name":"","models":[],"objects":[{"id":"SVO","model":"SVO3000","name":"板载-SVO"}]},{"name":"端口","type":"XPORTS","models":[{"name":"端口 1","id":"1","type":"XRJ25","func":"DHAK"},{"name":"端口 2","id":"2","type":"XRJ25","func":"DHP#"},{"name":"端口 3","id":"3","type":"XRJ25","func":"DHA#"},{"name":"端口 4","id":"4","type":"XRJ25","func":"DHP#"},{"name":"端口 5","id":"5","type":"XIP45","func":"U###"}]}]}';
      window.XBlockly.init(JSON.parse(jsonObjects));
      Blockly.Arduino.XBlockly_addInclude('Arduino', '#include <Arduino.h>');
      Blockly.Arduino.XBlockly_addInclude('PGKSystem', '#include <WKKSystem.h>');
      Blockly.Arduino.XBlockly_addSetup('PGKSystem', 'XSystem.setup();');
    }
    break;
    default: {
        var jsonObjects = '{"modules":[]}';
        window.XBlockly.init(JSON.parse(jsonObjects));
    }
    break;
  }
  return '';
};

Blockly.Arduino.xblockly_construct_XPORTS = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('PORT');
  var type = this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var objName = Blockly.Arduino.XBlockly_getModuleName(type,port);
  var globalCode = type + ' ' + objName + ';';
  Blockly.Arduino.XBlockly_addDeclaration(objName, globalCode);

  var setupCode = objName + '.setup(\"'
    + model
    + '\", \"'
    + port
    + '\");';
  Blockly.Arduino.XBlockly_addSetup(objName, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xiodriver_digitalRead = function() {
  var port = this.getFieldValue('XIODriver');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIODriver',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIODriver',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIODriver',port);
  var index = this.getFieldValue('INDEX');
  var code = name + '.digitalRead(' + index + ')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xiodriver_analogRead = function() {
  var port = this.getFieldValue('XIODriver');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIODriver',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIODriver',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIODriver',port);
  var index = this.getFieldValue('INDEX');
  var code = name + '.analogRead(' + index + ')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xiodriver_digitalWrite = function () {
  var port = this.getFieldValue('XIODriver');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIODriver',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIODriver',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIODriver',port);
  var index = this.getFieldValue('INDEX');
  var value = this.getFieldValue('VALUE');
  var code = name + '.digitalWrite(' + index + ',' + value + ');\n';
  return code;
};

  // Led
  Blockly.Arduino.xblockly_led = function() {
    var dropdown_pin = Blockly.Arduino.valueToCode(this, 'PIN',Blockly.Arduino.ORDER_ATOMIC);
    var dropdown_stat = Blockly.Arduino.valueToCode(this, 'STAT', Blockly.Arduino.ORDER_ATOMIC);
    // var dropdown_pin = this.getFieldValue('PIN');
    // var dropdown_stat = this.getFieldValue('STAT');
    Blockly.Arduino.setups_['setup_output_'+dropdown_pin] = 'pinMode('+dropdown_pin+', OUTPUT);';
    var code = 'digitalWrite('+dropdown_pin+','+dropdown_stat+');\n'
    return code;
  };


/********************************************
Move - 运动模块
*********************************************/
  
Blockly.Arduino.xblockly_xservo_setAngle = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XServo');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XServo',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XServo',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XServo',port);
  var angle = Blockly.Arduino.valueToCode(this, 'ANGLE',
          Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = name + '.setAngle(' + angle + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xservo_getAngle = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XServo');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XServo',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XServo',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XServo',port);
  var code = name + '.getAngle()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xdualdcmotor_turn = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XDualDCMotor');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XDualDCMotor',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XDualDCMotor',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XDualDCMotor',port);
  var index = this.getFieldValue('MOTOR');
  var dir = this.getFieldValue('DIR');
  var speed = Blockly.Arduino.valueToCode(this, 'SPEED',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  // TODO: Assemble JavaScript into code variable.
  var code;
  if(dir!=0) {
    speed = -speed;
  }
  if(index==1 || index==2) {
    code = name + '.setMotorSpeed(' + index + ',' + speed + ');\n';
  } else {
    code = name + '.setAllSpeed(' + speed + ',' + speed + ');\n';
  }
  return code;
};

Blockly.Arduino.xblockly_xdualdcmotor_stop = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XDualDCMotor');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XDualDCMotor',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XDualDCMotor',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XDualDCMotor',port);
  var index = this.getFieldValue('MOTOR');
  // TODO: Assemble JavaScript into code variable.
  var code;
  if(index==1 || index==2) {
    code = name + '.stopMotor(' + index + ');\n'; 
  } else {
    code = name + '.stopAllMotor();\n';
  }
  return code;
};

/********************************************
Sensor - 感知模块
*********************************************/

Blockly.Arduino.xblockly_xbutton_isPressed = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XButton');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XButton',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XButton',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XButton',port);
  var code = name + '.isPressed()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xbutton_waitPressed = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XButton');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XButton',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XButton',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XButton',port);
  var code = 'while(!' + name + '.isKnocked());\n';
  return code;
};

Blockly.Arduino.xblockly_xlightsensor_getLuminance = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XLightSensor');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLightSensor',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLightSensor',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLightSensor',port);
  var code = name + '.getLuminance()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xlightsensor_waitLuminance = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XLightSensor');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLightSensor',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLightSensor',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLightSensor',port);
  var event = this.getFieldValue('INDEX');
  var value = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = '';
  if(event==1) {
    code = 'while(' + name + '.getLuminance()<=' + value + ');\n';
  } else {
    code = 'while(' + name + '.getLuminance()>=' + value + ');\n';
  }
  return code;
};

Blockly.Arduino.xblockly_xsoundsensor_getVolume = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XSoundSensor');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XSoundSensor',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XSoundSensor',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XSoundSensor',port);
  var code = name + '.getVolume()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xsoundsensor_waitVolume = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XSoundSensor');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XSoundSensor',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XSoundSensor',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XSoundSensor',port);
  var event = this.getFieldValue('INDEX');
  var value = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = '';
  if(event==1) {
    code = 'while(' + name + '.getVolume()<=' + value + ');\n';
  } else {
    code = 'while(' + name + '.getVolume()>=' + value + ');\n';
  }
  return code;
};

Blockly.Arduino.xblockly_xirtracking_hasStatus = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XIRTracking');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRTracking',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIRTracking',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIRTracking',port);
  var status = this.getFieldValue('STATUS');
  var code = '(' + status + '==' + name + '.getStatus())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xirtracking_waitStatus = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XIRTracking');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRTracking',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIRTracking',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIRTracking',port);
  var event = this.getFieldValue('INDEX');
  var status = this.getFieldValue('STATUS');
  var code = '';
  if(event==1) {
    code = 'while(!(' + status + '==' + name + '.getStatus()));\n';
  } else {
    code = 'while(!(' + status + '==' + name + '.getStatus()));\n';
  }
  return code;
};

Blockly.Arduino.xblockly_xirtracking6_hasStatus = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XIRTracking6');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRTracking6',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIRTracking6',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIRTracking6',port);
  var status = this.getFieldValue('S1') | this.getFieldValue('S2') | this.getFieldValue('S3') 
  | this.getFieldValue('S4') | this.getFieldValue('S5') | this.getFieldValue('S6');
  var code = '(' + status + '==' + name + '.getStatus())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xirtracking6_waitStatus = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XIRTracking6');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRTracking6',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIRTracking6',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIRTracking6',port);
  var event = this.getFieldValue('INDEX');
  var status = this.getFieldValue('S1') | this.getFieldValue('S2') | this.getFieldValue('S3') 
  | this.getFieldValue('S4') | this.getFieldValue('S5') | this.getFieldValue('S6');
  var code = '';
  if(event==1) {
    code = 'while(!(' + status + '==' + name + '.getStatus()));\n';
  } else {
    code = 'while(!(' + status + '==' + name + '.getStatus()));\n';
  }
  return code;
};

Blockly.Arduino.xblockly_xultrasonic_getDistance = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XUltrasonic');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XUltrasonic',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XUltrasonic',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XUltrasonic',port);
  var code = '(' + name + '.getDistance()/10)';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xultrasonic_waitDistance = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XUltrasonic');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XUltrasonic',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XUltrasonic',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XUltrasonic',port);
  var event = this.getFieldValue('INDEX');
  var value = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = '';
  if(event==1) {
    code = 'while((' + name + '.getDistance()/10)<=' + value + ');\n';
  } else {
    code = 'while((' + name + '.getDistance()/10)>=' + value + ');\n';
  }
  return code;
};

Blockly.Arduino.xblockly_xiravoiding_start = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XIRAvoiding');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRAvoiding',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIRAvoiding',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIRAvoiding',port);
  var sensitive = Blockly.Arduino.valueToCode(this, 'SENSITIVE',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.start(' + sensitive + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xiravoiding_stop = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XIRAvoiding');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRAvoiding',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIRAvoiding',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIRAvoiding',port);
  var code = name + '.stop();\n';
  return code;
};

Blockly.Arduino.xblockly_xiravoiding_getStatus = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XIRAvoiding');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRAvoiding',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIRAvoiding',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIRAvoiding',port);
  var code = '(' + name + '.getStatus()==1)';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xiravoiding_waitStatus = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XIRAvoiding');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRAvoiding',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIRAvoiding',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIRAvoiding',port);
  var event = this.getFieldValue('EVENT');
  var code;
  if(event==1) {
    code = 'while(' + name + '.getStatus()!=1);\n';
  } else {
    code = 'while(' + name + '.getStatus()==1);\n';
  }
  return code;
};

Blockly.Arduino.xblockly_xpotentiometer_getValue = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XPotentiometer');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XPotentiometer',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XPotentiometer',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XPotentiometer',port);
  var code = name + '.getValue()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xpotentiometer_waitValue = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XPotentiometer');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XPotentiometer',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XPotentiometer',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XPotentiometer',port);
  var event = this.getFieldValue('INDEX');
  var value = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = '';
  if(event==1) {
    code = 'while(' + name + '.getValue()<=' + value + ');\n';
  } else {
    code = 'while(' + name + '.getValue()>=' + value + ');\n';
  }
  return code;
};

Blockly.Arduino.xblockly_xhumiture_getHumidity = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XHumiture');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XHumiture',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XHumiture',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XHumiture',port);
  var code = name + '.getHumidity()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xhumiture_getTemperature = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XHumiture');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XHumiture',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XHumiture',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XHumiture',port);
  var code = name + '.getTemperature()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xhumiture_waitHumidity = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XHumiture');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XHumiture',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XHumiture',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XHumiture',port);
  var event = this.getFieldValue('INDEX');
  var value = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code;
  if(event==1) {
    code = 'while(' + name + '.getHumidity()<=' + value + ');\n';
  } else {
    code = 'while(' + name + '.getHumidity()>=' + value + ');\n';
  }
  return code;
};

Blockly.Arduino.xblockly_xhumiture_waitTemperature = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XHumiture');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XHumiture',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XHumiture',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XHumiture',port);
  var event = this.getFieldValue('INDEX');
  var value = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code;
  if(event==3) {
    code = 'while(' + name + '.getTemperature()<=' + value + ');\n';
  } else {
    code = 'while(' + name + '.getTemperature()>=' + value + ');\n';
  }
  return code;
};

Blockly.Arduino.xblockly_xpir_isMotionDetected = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XPIR');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XPIR',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XPIR',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XPIR',port);
  var code = name + '.isHumanMotionDetected()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xpir_waitMotion = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XPIR');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XPIR',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XPIR',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XPIR',port);
  var event = this.getFieldValue('INDEX');
  var code = '';
  if(event==1) {
    code = 'while(!(' + name + '.isHumanMotionDetected()));\n';
  } else {
    code = 'while(' + name + '.isHumanMotionDetected());\n';
  }
  return code;
};

Blockly.Arduino.xblockly_xshocksensor_isShocking = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XShockSensor');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XShockSensor',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XShockSensor',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XShockSensor',port);
  var code = '(' + name + '.isShocking()==1)';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xshocksensor_waitStatus = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XShockSensor');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XShockSensor',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XShockSensor',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XShockSensor',port);
  var event = this.getFieldValue('EVENT');
  var code;
  if(event==1) {
    code = 'while(!(' + name + '.isShocking()));\n';
  } else {
    code = 'while(' + name + '.isShocking());\n';
  }
  return code;
};

/********************************************
Display - 展示模块
*********************************************/

Blockly.Arduino.xblockly_xsegdisplay_showNumber = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XSegDisplay');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XSegDisplay',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XSegDisplay',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XSegDisplay',port);
  var number = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = name + '.showNumber((float)' + number + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xsegdisplay_showNumberEx = function() {
  Blockly.Arduino.XBlockly_addGlobal();
var port = this.getFieldValue('XSegDisplay');
if(Blockly.Arduino.XBlockly_isOnBoardModule('XSegDisplay',port)) {
  Blockly.Arduino.XBlockly_addOnBoardModule('XSegDisplay',port);
}
var name = Blockly.Arduino.XBlockly_getModuleName('XSegDisplay',port);
var number = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_ATOMIC) || 0;
var format = this.getFieldValue('FORMAT');
var code = name + '.showNumber((uint32_t)' + number + ',' + format + ');\n';
return code;
};

Blockly.Arduino.xblockly_xsegdisplay_showCharacter = function() {
  Blockly.Arduino.XBlockly_addGlobal();
var port = this.getFieldValue('XSegDisplay');
if(Blockly.Arduino.XBlockly_isOnBoardModule('XSegDisplay',port)) {
  Blockly.Arduino.XBlockly_addOnBoardModule('XSegDisplay',port);
}
var name = Blockly.Arduino.XBlockly_getModuleName('XSegDisplay',port);
var index = this.getFieldValue('INDEX');
var number = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_ATOMIC) || 0;
var code = name + '.showCharacter(' + index + ',' + number + ');\n';
return code;
};

Blockly.Arduino.xblockly_xsegdisplay_showSegment = function() {
  Blockly.Arduino.XBlockly_addGlobal();
var port = this.getFieldValue('XSegDisplay');
if(Blockly.Arduino.XBlockly_isOnBoardModule('XSegDisplay',port)) {
  Blockly.Arduino.XBlockly_addOnBoardModule('XSegDisplay',port);
}
var name = Blockly.Arduino.XBlockly_getModuleName('XSegDisplay',port);
var index = this.getFieldValue('INDEX');
var segment = this.getFieldValue('VALUE');
var code = name + '.showSegment(' + index + ',\'' + segment + '\');\n';
return code;
};

Blockly.Arduino.xblockly_xsegdisplay_clearSegment = function() {
  Blockly.Arduino.XBlockly_addGlobal();
var port = this.getFieldValue('XSegDisplay');
if(Blockly.Arduino.XBlockly_isOnBoardModule('XSegDisplay',port)) {
  Blockly.Arduino.XBlockly_addOnBoardModule('XSegDisplay',port);
}
var name = Blockly.Arduino.XBlockly_getModuleName('XSegDisplay',port);
var index = this.getFieldValue('INDEX');
var segment = this.getFieldValue('VALUE');
var code = name + '.clearSegment(' + index + ',\'' + segment + '\');\n';
return code;
};

Blockly.Arduino.xblockly_xsegdisplay_clear = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XSegDisplay');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XSegDisplay',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XSegDisplay',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XSegDisplay',port);
  var index = this.getFieldValue('INDEX');
  var code = name + '.clear(' + index + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_move = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLEDMatrix',port);
  var x = Blockly.Arduino.valueToCode(this, 'X',
    Blockly.Arduino.ORDER_NONE) || 0;
  var y = Blockly.Arduino.valueToCode(this, 'Y',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.move(' + x + ',' + y + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_setBrightness = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLEDMatrix',port);
  var val = this.getFieldValue('VALUE');
  var code = name + '.setBrightness(' + val + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_setColorInverse = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLEDMatrix',port);
  var val = this.getFieldValue('VALUE');
  var code = name + '.setColorInverse(' + val + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_setEffect = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLEDMatrix',port);
  var effect = this.getFieldValue('EFFECT');
  var speed = this.getFieldValue('SPEED');
  var code = name + '.setEffect(' + effect + ',' + speed + ');\n';
  return code;
};

//显示 - 自定义图案数组
Blockly.Arduino.xblockly_xledmatrix_matrix = function() {
  var val = 0;
  var code = '';
  for(var row = 0 ; row < 8; row ++) {
    for (var col = 0; col < 16; col++) {
      if((this.getFieldValue(row + '_' + col) == 'TRUE')) {
        val += row * 16 + col + 1;
        code +=  '1';
      } else {
        code += '0';
      }
    }
  }
  code = code + ',' + val;
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xledmatrix_showBitmap = function () {
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLEDMatrix',port);
  var val = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_NONE) || '';
  var code = '';
  if(val.length >= 128) {
    var arr = val.split(',');
    var tmp = new Array(128);
    for(var i = 0; i < 8; i++)
    {
      for(var j = 0; j < 16; j++)
      {
        tmp[j*8 + i] = val[i*16 + j];
      }
    }
    tmp = tmp.join("");
    var globalName = 'bitmap_' + arr[1];
    var globalCode = 'uint8_t bitmap_' + arr[1] + '[] = {\n' 
    + Blockly.Arduino.INDENT + ' /*' + tmp.substr(0,8) +'*/' + parseInt(tmp.substr(0,8),2) + '\n'
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(8,8) +'*/' + parseInt(tmp.substr(8,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(16,8) +'*/' + parseInt(tmp.substr(16,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(24,8) +'*/' + parseInt(tmp.substr(24,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(32,8) +'*/' + parseInt(tmp.substr(32,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(40,8) +'*/' + parseInt(tmp.substr(40,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(48,8) +'*/' + parseInt(tmp.substr(48,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(56,8) +'*/' + parseInt(tmp.substr(56,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(64,8) +'*/' + parseInt(tmp.substr(64,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(72,8) +'*/' + parseInt(tmp.substr(72,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(80,8) +'*/' + parseInt(tmp.substr(80,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(88,8) +'*/' + parseInt(tmp.substr(88,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(96,8) +'*/' + parseInt(tmp.substr(96,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(104,8) +'*/' + parseInt(tmp.substr(104,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(112,8) +'*/' + parseInt(tmp.substr(112,8),2) + '\n' 
    + Blockly.Arduino.INDENT + ',/*' + tmp.substr(120,8) +'*/' + parseInt(tmp.substr(120,8),2) + '\n' 
    + '};';
    Blockly.Arduino.XBlockly_addDeclaration(globalName, globalCode);
    code = name + '.showBitmap(' + globalName + ', 16);\n';
  } else {
    code = name + '.showBitmap(\"' + val + '\",' + val.length + ');\n';
  }
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_showNumber = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLEDMatrix',port);
  var num = Blockly.Arduino.valueToCode(this, 'NUM',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.showNumber(' + num + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_showNumberPair = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLEDMatrix',port);
  var a = Blockly.Arduino.valueToCode(this, 'A',
    Blockly.Arduino.ORDER_NONE) || 0;
  var b = Blockly.Arduino.valueToCode(this, 'B',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.showNumberPair(' + a + ',' + b + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_showString = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLEDMatrix',port);
  var val = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_NONE) || '';
  var code = name + '.showString(' + val + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_showEmoticon = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLEDMatrix',port);
  var emot = this.getFieldValue('EMOTION');
  var code = name + '.showEmoticon(' + emot + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_showFlag = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLEDMatrix',port);
  var index = this.getFieldValue('INDEX');
  var value = this.getFieldValue('VALUE');
  var code = name + '.showFlag(' + value + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_clear = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XLEDMatrix',port);
  var code = name + '.clear();\n';
  return code;
};

Blockly.Arduino.xblockly_xvoicebroadcast_reportObject = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XVoiceBroadcast',port);
  var index = this.getFieldValue('INDEX');
  var value = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_NONE) || 0;
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportObject(' + index + ',' + value + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xvoicebroadcast_reportTime = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XVoiceBroadcast',port);
  //var time = Blockly.Arduino.valueToCode(this, 'VALUE',
  //    Blockly.Arduino.ORDER_NONE) || 0;
  var hour = Blockly.Arduino.valueToCode(this, 'HOUR',
      Blockly.Arduino.ORDER_NONE) || 0;
  var minute = Blockly.Arduino.valueToCode(this, 'MINUTE',
      Blockly.Arduino.ORDER_NONE) || 0;
  var second = Blockly.Arduino.valueToCode(this, 'SECOND',
      Blockly.Arduino.ORDER_NONE) || 0;
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportTime(' + hour + ',' + minute + ',' + second + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xvoicebroadcast_reportDate = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XVoiceBroadcast',port);
  //var date = Blockly.Arduino.valueToCode(this, 'VALUE',
  //    Blockly.Arduino.ORDER_NONE) || 0;
  var year = Blockly.Arduino.valueToCode(this, 'YEAR',
      Blockly.Arduino.ORDER_NONE) || 0;
  var month = Blockly.Arduino.valueToCode(this, 'MONTH',
      Blockly.Arduino.ORDER_NONE) || 0;
  var day = Blockly.Arduino.valueToCode(this, 'DAY',
      Blockly.Arduino.ORDER_NONE) || 0;
  //var weekday = this.getFieldValue('WEEKDAY');
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportDate(' + year + ',' + month + ',' + day + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xvoicebroadcast_reportOperator = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XVoiceBroadcast',port);
  var index = this.getFieldValue('INDEX');
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportOperator(' + index + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xvoicebroadcast_reportSound = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XVoiceBroadcast',port);
  //var index = this.getFieldValue('INDEX');
  var value = this.getFieldValue('VALUE');
  var repeat = (this.getFieldValue('REPEAT') == 'TRUE') ? 1 : 0;
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportSound(' + value + ',' + repeat + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xvoicebroadcast_stop = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XVoiceBroadcast',port);
  // TODO: Assemble Arduino into code variable.
  var code = name + '.stop();\n';
  return code;
};

Blockly.Arduino.xblockly_xvoicebroadcast_isPlaying = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XVoiceBroadcast',port);
  var code = name + '.isPlaying()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xpgklightshow_showColor = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XRGBLed');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XRGBLed',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XRGBLed',port);
  }
  var arrObjs = [{type:'XRGBLed',port:port}];
  Blockly.Arduino.XBlockly_addService('PGKLightShow', 'lgs', arrObjs);
  var objName = Blockly.Arduino.XBlockly_getServiceName('PGKLightShow', 'lgs', arrObjs);
  var index = this.getFieldValue('INDEX');
  // var color = Blockly.Arduino.valueToCode(this, 'COLOR',
  //         Blockly.Arduino.ORDER_ATOMIC) || 0;
  var clrString = this.getFieldValue('COLOR');
  /*var r = parseInt(clrString.substring(1, 3), 16);
  var g = parseInt(clrString.substring(3, 5), 16);
  var b = parseInt(clrString.substring(5, 7), 16);
  var color = 0;
  color |= (b&0xff);
  color |= ((g<<8)&0xff00);
  color |= ((r<<16)&0xff0000);*/
  var color = goog.color.hexToRgb(clrString);
  var code = objName + '.showColor(' + index + ',' + color + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xpgklightshow_showRGB = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XRGBLed');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XRGBLed',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XRGBLed',port);
  }
  var arrObjs = [{type:'XRGBLed',port:port}];
  Blockly.Arduino.XBlockly_addService('PGKLightShow', 'lgs', arrObjs);
  var objName = Blockly.Arduino.XBlockly_getServiceName('PGKLightShow', 'lgs', arrObjs);
  var index = this.getFieldValue('INDEX');
  var r = Blockly.Arduino.valueToCode(this, 'R',
          Blockly.Arduino.ORDER_ATOMIC) || 0;
  var g = Blockly.Arduino.valueToCode(this, 'G',
          Blockly.Arduino.ORDER_ATOMIC) || 0;
  var b = Blockly.Arduino.valueToCode(this, 'B',
          Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = objName + '.showColor(' + index + ',' + r + ',' + g + ',' + b + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xpgklightshow_clear = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XRGBLed');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XRGBLed',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XRGBLed',port);
  }
  var arrObjs = [{type:'XRGBLed',port:port}];
  Blockly.Arduino.XBlockly_addService('PGKLightShow', 'lgs', arrObjs);
  var objName = Blockly.Arduino.XBlockly_getServiceName('PGKLightShow', 'lgs', arrObjs);
  var index = this.getFieldValue('INDEX');
  var code = objName + '.clear(' + index + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xpgkaudioplayer_playTone = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XBuzzer');
  if (Blockly.Arduino.XBlockly_isOnBoardModule('XBuzzer', port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XBuzzer', port);
  }
  var arrObjs = [{ type: 'XBuzzer', port: port }];
  Blockly.Arduino.XBlockly_addService('PGKAudioPlayer', 'adp', arrObjs);
  var objName = Blockly.Arduino.XBlockly_getServiceName('PGKAudioPlayer', 'adp', arrObjs);
  var frequency = Blockly.Arduino.valueToCode(this, 'FREQUENCY',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var duration = Blockly.Arduino.valueToCode(this, 'DURATION',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = objName + '.playTone(' + frequency + ', ' + duration + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xpgkaudioplayer_setNoteParameter = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XBuzzer');
  if (Blockly.Arduino.XBlockly_isOnBoardModule('XBuzzer', port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XBuzzer', port);
  }
  var arrObjs = [{ type: 'XBuzzer', port: port }];
  Blockly.Arduino.XBlockly_addService('PGKAudioPlayer', 'adp', arrObjs);
  var objName = Blockly.Arduino.XBlockly_getServiceName('PGKAudioPlayer', 'adp', arrObjs);
  var beattime = Blockly.Arduino.valueToCode(this, 'BEATTIME',
    Blockly.Arduino.ORDER_ATOMIC) || 0;
  //0.1秒就是100ms, 2秒就是2000，对应beatTime分别就是10和200, 然后转换为一个字节
  if (beattime < 0.1) {
    beattime = 0.1;
  } else if (beattime > 2.0) {
    beattime = 2.0;
  }
  beattime *= 100;
  var code = objName + '.setNoteParameter(' + beattime + ',0);\n';
  return code;
};

Blockly.Arduino.xblockly_xpgkaudioplayer_playNote = function () {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XBuzzer');
  if (Blockly.Arduino.XBlockly_isOnBoardModule('XBuzzer', port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XBuzzer', port);
  }
  var arrObjs = [{ type: 'XBuzzer', port: port }];
  Blockly.Arduino.XBlockly_addService('PGKAudioPlayer', 'adp', arrObjs);
  var objName = Blockly.Arduino.XBlockly_getServiceName('PGKAudioPlayer', 'adp', arrObjs);
  var note = this.getFieldValue('NOTE');
  var scale = this.getFieldValue('SCALE');
  var tone = this.getFieldValue('TONE');
  var beat = this.getFieldValue('BEAT');
  var code = objName + '.playNote(' + note + ',' + scale + ',' + tone + ',' + beat + ');\n';
  return code;
};

/********************************************
Communicator - 通信模块
*********************************************/

Blockly.Arduino.xblockly_xirreceiver_presskey = function() {
  var dropdown_press_key = this.getFieldValue('PRESSKEY');
var code = dropdown_press_key;
return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xirreceiver_enableLongPress = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XIRReceiver');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRReceiver',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIRReceiver',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIRReceiver',port);
  // var val = Blockly.Arduino.valueToCode(this, 'VALUE',
  //     Blockly.Arduino.ORDER_NONE) || 0;
  var val = this.getFieldValue('PRESSKEY');
  var code = name + '.enableLongPress(' + val + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xirreceiver_available = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XIRReceiver');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRReceiver',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIRReceiver',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIRReceiver',port);
  var code = '(0xFF!=' + name + '.receive())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xirreceiver_receiveNumber = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XIRReceiver');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRReceiver',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIRReceiver',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIRReceiver',port);
  // var val = Blockly.Arduino.valueToCode(this, 'VALUE',
  //     Blockly.Arduino.ORDER_NONE) || 0;
  var val = this.getFieldValue('PRESSKEY');
  var code = '(' + val + '==' + name + '.pick())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xirreceiver_waitMessage = function() {
  Blockly.Arduino.XBlockly_addGlobal();
  var port = this.getFieldValue('XIRReceiver');
  if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRReceiver',port)) {
    Blockly.Arduino.XBlockly_addOnBoardModule('XIRReceiver',port);
  }
  var name = Blockly.Arduino.XBlockly_getModuleName('XIRReceiver',port);
  var code = name + '.wait();\n';
  return code;
};

/********************************************
System - 系统模块
*********************************************/
