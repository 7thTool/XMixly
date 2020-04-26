'use strict';

goog.provide('Blockly.Arduino.wkkit');

goog.require('Blockly.Arduino');
goog.require('Blockly.JavaScript');

Blockly.Arduino.WKKit_statementToCodeNoTab = function (block, name) {
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

Blockly.Arduino.WKKit_addInclude = function (tag,code) {
  Blockly.Arduino.definitions_['define_' + tag] = code;
}

Blockly.Arduino.WKKit_addDeclaration = function (tag, code) {
  Blockly.Arduino.definitions_['var_' + tag] = code;
}

Blockly.Arduino.WKKit_addFunction = function (tag, code) {
  Blockly.Arduino.definitions_[tag] = code;
}

Blockly.Arduino.WKKit_addSetup = function (tag, code) {
  Blockly.Arduino.setups_['setup_' + tag] = code;
}

Blockly.Arduino.WKKit_addGlobal = function () {
  //只要使用了wkkit，强制添加wkkit全局代码
  Blockly.Arduino.WKKit_addInclude('Arduino', '#include <Arduino.h>');
  Blockly.Arduino.WKKit_addInclude('WKKSystem', '#include <WKKSystem.h>');
  Blockly.Arduino.WKKit_addSetup('WKKSystem', 'XSystem.setup();');
}

Blockly.Arduino.WKKit_addOnBoardModule = function (type, label) {
  Blockly.Arduino.WKKit_addInclude(type, '#include <' + type + '.h>');
  var objName = label.toLowerCase();
  var globalCode = type + ' ' + objName + ';';
  Blockly.Arduino.WKKit_addDeclaration(objName, globalCode);
  var setupCode = objName + '.setup(\"' + label + '\");';
  Blockly.Arduino.WKKit_addSetup(objName, setupCode);
  //Blockly.Arduino.reservePort(label,objName);
}

Blockly.Arduino.WKKit_isOnBoardModule = function (type, label) {
  if(type && label) {
      if(isNaN(label)) { //简单判断一下
          return true;
      }
  }
  return false;
}

Blockly.Arduino.WKKit_getModuleName = function (type,port) {
  var name = "";
  var typeObj = window.WKKit.getTypeObj(type);
  if (typeObj) {
      if (typeObj.type == 'XIODriver') {
          name = ('io_' + port).toLowerCase();
      } else {
          if (Blockly.Arduino.WKKit_isOnBoardModule(typeObj.type, port)) {
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
Blockly.Arduino.WKKit_addService = function (type, n3c, objs) {
  Blockly.Arduino.WKKit_addInclude(type, '#include <' + type + '.h>');
  var objName = n3c;
  for(var i=0;i<objs.length;i++) {
      objName += '_' + Blockly.Arduino.WKKit_getModuleName(objs[i].type, objs[i].port);
  }
  var globalCode = type + ' ' + objName + ';';
  Blockly.Arduino.WKKit_addDeclaration(objName, globalCode);
  var setupCode = objName + '.setup(';
  for(var i=0;i<objs.length;i++) {
      setupCode += '&' + Blockly.Arduino.WKKit_getModuleName(objs[i].type, objs[i].port);
  }
  setupCode += ');';
  Blockly.Arduino.WKKit_addSetup(objName, setupCode);
  //var loopCode = objName + '.loop();';
  //Blockly.Arduino.addLoop(objName, loopCode, true);
}

Blockly.Arduino.WKKit_getServiceName = function (type, n3c, objs) {
  var objName = n3c;
  for(var i=0;i<objs.length;i++) {
      objName += '_' + Blockly.Arduino.WKKit_getModuleName(objs[i].type, objs[i].port);
  }
  return objName;
}


/********************************************
Construct - 连接模块
*********************************************/

Blockly.Arduino.wkkit_construct_XPORTS = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('PORT');
  var type = this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  Blockly.Arduino.WKKit_addInclude(type, '#include <' + type + '.h>');

  var objName = Blockly.Arduino.WKKit_getModuleName(type,port);
  var globalCode = type + ' ' + objName + ';';
  Blockly.Arduino.WKKit_addDeclaration(objName, globalCode);

  var setupCode = objName + '.setup(\"'
    + model
    + '\", \"'
    + port
    + '\");';
  Blockly.Arduino.WKKit_addSetup(objName, setupCode);

  return '';
};

Blockly.Arduino.wkkit_xiodriver_digitalRead = function() {
  var port = this.getFieldValue('XIODriver');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIODriver',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIODriver',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIODriver',port);
  var index = this.getFieldValue('INDEX');
  var code = name + '.digitalRead(' + index + ')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xiodriver_analogRead = function() {
  var port = this.getFieldValue('XIODriver');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIODriver',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIODriver',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIODriver',port);
  var index = this.getFieldValue('INDEX');
  var code = name + '.analogRead(' + index + ')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xiodriver_digitalWrite = function () {
  var port = this.getFieldValue('XIODriver');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIODriver',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIODriver',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIODriver',port);
  var index = this.getFieldValue('INDEX');
  var value = this.getFieldValue('VALUE');
  var code = name + '.digitalWrite(' + index + ',' + value + ');\n';
  return code;
};

  // Led
  Blockly.Arduino.wkkit_led = function() {
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
  
Blockly.Arduino.wkkit_xservo_setAngle = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XServo');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XServo',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XServo',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XServo',port);
  var angle = Blockly.Arduino.valueToCode(this, 'ANGLE',
          Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = name + '.setAngle(' + angle + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xservo_getAngle = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XServo');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XServo',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XServo',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XServo',port);
  var code = name + '.getAngle()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xdualdcmotor_turn = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XDualDCMotor');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XDualDCMotor',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XDualDCMotor',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XDualDCMotor',port);
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

Blockly.Arduino.wkkit_xdualdcmotor_stop = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XDualDCMotor');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XDualDCMotor',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XDualDCMotor',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XDualDCMotor',port);
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

Blockly.Arduino.wkkit_xbutton_isPressed = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XButton');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XButton',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XButton',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XButton',port);
  var code = name + '.isPressed()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xbutton_waitPressed = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XButton');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XButton',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XButton',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XButton',port);
  var code = 'while(!' + name + '.isKnocked());\n';
  return code;
};

Blockly.Arduino.wkkit_xlightsensor_getLuminance = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XLightSensor');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLightSensor',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLightSensor',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLightSensor',port);
  var code = name + '.getLuminance()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xlightsensor_waitLuminance = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XLightSensor');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLightSensor',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLightSensor',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLightSensor',port);
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

Blockly.Arduino.wkkit_xsoundsensor_getVolume = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XSoundSensor');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XSoundSensor',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XSoundSensor',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XSoundSensor',port);
  var code = name + '.getVolume()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xsoundsensor_waitVolume = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XSoundSensor');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XSoundSensor',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XSoundSensor',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XSoundSensor',port);
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

Blockly.Arduino.wkkit_xirtracking_hasStatus = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XIRTracking');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIRTracking',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIRTracking',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIRTracking',port);
  var status = this.getFieldValue('STATUS');
  var code = '(' + status + '==' + name + '.getStatus())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xirtracking_waitStatus = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XIRTracking');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIRTracking',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIRTracking',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIRTracking',port);
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

Blockly.Arduino.wkkit_xirtracking6_hasStatus = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XIRTracking6');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIRTracking6',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIRTracking6',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIRTracking6',port);
  var status = this.getFieldValue('S1') | this.getFieldValue('S2') | this.getFieldValue('S3') 
  | this.getFieldValue('S4') | this.getFieldValue('S5') | this.getFieldValue('S6');
  var code = '(' + status + '==' + name + '.getStatus())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xirtracking6_waitStatus = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XIRTracking6');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIRTracking6',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIRTracking6',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIRTracking6',port);
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

Blockly.Arduino.wkkit_xultrasonic_getDistance = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XUltrasonic');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XUltrasonic',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XUltrasonic',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XUltrasonic',port);
  var code = '(' + name + '.getDistance()/10)';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xultrasonic_waitDistance = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XUltrasonic');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XUltrasonic',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XUltrasonic',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XUltrasonic',port);
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

Blockly.Arduino.wkkit_xiravoiding_start = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XIRAvoiding');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIRAvoiding',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIRAvoiding',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIRAvoiding',port);
  var sensitive = Blockly.Arduino.valueToCode(this, 'SENSITIVE',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.start(' + sensitive + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xiravoiding_stop = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XIRAvoiding');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIRAvoiding',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIRAvoiding',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIRAvoiding',port);
  var code = name + '.stop();\n';
  return code;
};

Blockly.Arduino.wkkit_xiravoiding_getStatus = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XIRAvoiding');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIRAvoiding',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIRAvoiding',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIRAvoiding',port);
  var code = '(' + name + '.getStatus()==1)';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xiravoiding_waitStatus = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XIRAvoiding');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIRAvoiding',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIRAvoiding',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIRAvoiding',port);
  var event = this.getFieldValue('EVENT');
  var code;
  if(event==1) {
    code = 'while(' + name + '.getStatus()!=1);\n';
  } else {
    code = 'while(' + name + '.getStatus()==1);\n';
  }
  return code;
};

Blockly.Arduino.wkkit_xpotentiometer_getValue = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XPotentiometer');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XPotentiometer',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XPotentiometer',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XPotentiometer',port);
  var code = name + '.getValue()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xpotentiometer_waitValue = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XPotentiometer');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XPotentiometer',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XPotentiometer',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XPotentiometer',port);
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

Blockly.Arduino.wkkit_xhumiture_getHumidity = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XHumiture');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XHumiture',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XHumiture',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XHumiture',port);
  var code = name + '.getHumidity()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xhumiture_getTemperature = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XHumiture');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XHumiture',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XHumiture',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XHumiture',port);
  var code = name + '.getTemperature()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xhumiture_waitHumidity = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XHumiture');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XHumiture',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XHumiture',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XHumiture',port);
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

Blockly.Arduino.wkkit_xhumiture_waitTemperature = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XHumiture');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XHumiture',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XHumiture',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XHumiture',port);
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

Blockly.Arduino.wkkit_xpir_isMotionDetected = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XPIR');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XPIR',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XPIR',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XPIR',port);
  var code = name + '.isHumanMotionDetected()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xpir_waitMotion = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XPIR');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XPIR',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XPIR',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XPIR',port);
  var event = this.getFieldValue('INDEX');
  var code = '';
  if(event==1) {
    code = 'while(!(' + name + '.isHumanMotionDetected()));\n';
  } else {
    code = 'while(' + name + '.isHumanMotionDetected());\n';
  }
  return code;
};

Blockly.Arduino.wkkit_xshocksensor_isShocking = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XShockSensor');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XShockSensor',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XShockSensor',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XShockSensor',port);
  var code = '(' + name + '.isShocking()==1)';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xshocksensor_waitStatus = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XShockSensor');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XShockSensor',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XShockSensor',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XShockSensor',port);
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

Blockly.Arduino.wkkit_xsegdisplay_showNumber = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XSegDisplay');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XSegDisplay',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XSegDisplay',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XSegDisplay',port);
  var number = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = name + '.showNumber((float)' + number + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xsegdisplay_showNumberEx = function() {
  Blockly.Arduino.WKKit_addGlobal();
var port = this.getFieldValue('XSegDisplay');
if(Blockly.Arduino.WKKit_isOnBoardModule('XSegDisplay',port)) {
  Blockly.Arduino.WKKit_addOnBoardModule('XSegDisplay',port);
}
var name = Blockly.Arduino.WKKit_getModuleName('XSegDisplay',port);
var number = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_ATOMIC) || 0;
var format = this.getFieldValue('FORMAT');
var code = name + '.showNumber((uint32_t)' + number + ',' + format + ');\n';
return code;
};

Blockly.Arduino.wkkit_xsegdisplay_showCharacter = function() {
  Blockly.Arduino.WKKit_addGlobal();
var port = this.getFieldValue('XSegDisplay');
if(Blockly.Arduino.WKKit_isOnBoardModule('XSegDisplay',port)) {
  Blockly.Arduino.WKKit_addOnBoardModule('XSegDisplay',port);
}
var name = Blockly.Arduino.WKKit_getModuleName('XSegDisplay',port);
var index = this.getFieldValue('INDEX');
var number = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_ATOMIC) || 0;
var code = name + '.showCharacter(' + index + ',' + number + ');\n';
return code;
};

Blockly.Arduino.wkkit_xsegdisplay_showSegment = function() {
  Blockly.Arduino.WKKit_addGlobal();
var port = this.getFieldValue('XSegDisplay');
if(Blockly.Arduino.WKKit_isOnBoardModule('XSegDisplay',port)) {
  Blockly.Arduino.WKKit_addOnBoardModule('XSegDisplay',port);
}
var name = Blockly.Arduino.WKKit_getModuleName('XSegDisplay',port);
var index = this.getFieldValue('INDEX');
var segment = this.getFieldValue('VALUE');
var code = name + '.showSegment(' + index + ',\'' + segment + '\');\n';
return code;
};

Blockly.Arduino.wkkit_xsegdisplay_clearSegment = function() {
  Blockly.Arduino.WKKit_addGlobal();
var port = this.getFieldValue('XSegDisplay');
if(Blockly.Arduino.WKKit_isOnBoardModule('XSegDisplay',port)) {
  Blockly.Arduino.WKKit_addOnBoardModule('XSegDisplay',port);
}
var name = Blockly.Arduino.WKKit_getModuleName('XSegDisplay',port);
var index = this.getFieldValue('INDEX');
var segment = this.getFieldValue('VALUE');
var code = name + '.clearSegment(' + index + ',\'' + segment + '\');\n';
return code;
};

Blockly.Arduino.wkkit_xsegdisplay_clear = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XSegDisplay');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XSegDisplay',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XSegDisplay',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XSegDisplay',port);
  var index = this.getFieldValue('INDEX');
  var code = name + '.clear(' + index + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xledmatrix_move = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLEDMatrix',port);
  var x = Blockly.Arduino.valueToCode(this, 'X',
    Blockly.Arduino.ORDER_NONE) || 0;
  var y = Blockly.Arduino.valueToCode(this, 'Y',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.move(' + x + ',' + y + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xledmatrix_setBrightness = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLEDMatrix',port);
  var val = this.getFieldValue('VALUE');
  var code = name + '.setBrightness(' + val + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xledmatrix_setColorInverse = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLEDMatrix',port);
  var val = this.getFieldValue('VALUE');
  var code = name + '.setColorInverse(' + val + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xledmatrix_setEffect = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLEDMatrix',port);
  var effect = this.getFieldValue('EFFECT');
  var speed = this.getFieldValue('SPEED');
  var code = name + '.setEffect(' + effect + ',' + speed + ');\n';
  return code;
};

//显示 - 自定义图案数组
Blockly.Arduino.wkkit_xledmatrix_matrix = function() {
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

Blockly.Arduino.wkkit_xledmatrix_showBitmap = function () {
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLEDMatrix',port);
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
    Blockly.Arduino.WKKit_addDeclaration(globalName, globalCode);
    code = name + '.showBitmap(' + globalName + ', 16);\n';
  } else {
    code = name + '.showBitmap(\"' + val + '\",' + val.length + ');\n';
  }
  return code;
};

Blockly.Arduino.wkkit_xledmatrix_showNumber = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLEDMatrix',port);
  var num = Blockly.Arduino.valueToCode(this, 'NUM',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.showNumber(' + num + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xledmatrix_showNumberPair = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLEDMatrix',port);
  var a = Blockly.Arduino.valueToCode(this, 'A',
    Blockly.Arduino.ORDER_NONE) || 0;
  var b = Blockly.Arduino.valueToCode(this, 'B',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.showNumberPair(' + a + ',' + b + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xledmatrix_showString = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLEDMatrix',port);
  var val = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_NONE) || '';
  var code = name + '.showString(' + val + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xledmatrix_showEmoticon = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLEDMatrix',port);
  var emot = this.getFieldValue('EMOTION');
  var code = name + '.showEmoticon(' + emot + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xledmatrix_showFlag = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLEDMatrix',port);
  var index = this.getFieldValue('INDEX');
  var value = this.getFieldValue('VALUE');
  var code = name + '.showFlag(' + value + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xledmatrix_clear = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XLEDMatrix',port);
  var code = name + '.clear();\n';
  return code;
};

Blockly.Arduino.wkkit_xvoicebroadcast_reportObject = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XVoiceBroadcast',port);
  var index = this.getFieldValue('INDEX');
  var value = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_NONE) || 0;
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportObject(' + index + ',' + value + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xvoicebroadcast_reportTime = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XVoiceBroadcast',port);
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

Blockly.Arduino.wkkit_xvoicebroadcast_reportDate = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XVoiceBroadcast',port);
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

Blockly.Arduino.wkkit_xvoicebroadcast_reportOperator = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XVoiceBroadcast',port);
  var index = this.getFieldValue('INDEX');
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportOperator(' + index + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xvoicebroadcast_reportSound = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XVoiceBroadcast',port);
  //var index = this.getFieldValue('INDEX');
  var value = this.getFieldValue('VALUE');
  var repeat = (this.getFieldValue('REPEAT') == 'TRUE') ? 1 : 0;
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportSound(' + value + ',' + repeat + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xvoicebroadcast_stop = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XVoiceBroadcast',port);
  // TODO: Assemble Arduino into code variable.
  var code = name + '.stop();\n';
  return code;
};

Blockly.Arduino.wkkit_xvoicebroadcast_isPlaying = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XVoiceBroadcast',port);
  var code = name + '.isPlaying()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xwkklightshow_showColor = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XRGBLed');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XRGBLed',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XRGBLed',port);
  }
  var arrObjs = [{type:'XRGBLed',port:port}];
  Blockly.Arduino.WKKit_addService('WKKLightShow', 'lgs', arrObjs);
  var objName = Blockly.Arduino.WKKit_getServiceName('WKKLightShow', 'lgs', arrObjs);
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

Blockly.Arduino.wkkit_xwkklightshow_showRGB = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XRGBLed');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XRGBLed',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XRGBLed',port);
  }
  var arrObjs = [{type:'XRGBLed',port:port}];
  Blockly.Arduino.WKKit_addService('WKKLightShow', 'lgs', arrObjs);
  var objName = Blockly.Arduino.WKKit_getServiceName('WKKLightShow', 'lgs', arrObjs);
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

Blockly.Arduino.wkkit_xwkklightshow_showBreath = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XRGBLed');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XRGBLed',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XRGBLed',port);
  }
  var arrObjs = [{type:'XRGBLed',port:port}];
  Blockly.Arduino.WKKit_addService('WKKLightShow', 'lgs', arrObjs);
  var objName = Blockly.Arduino.WKKit_getServiceName('WKKLightShow', 'lgs', arrObjs);
  var index = this.getFieldValue('INDEX');
  //var val = Blockly.Arduino.valueToCode(block, 'VALUE',
  //        Blockly.Arduino.ORDER_NONE) || 0;
  var val = this.getFieldValue('VALUE');
  var clrString = this.getFieldValue('COLOR');
  var color = goog.color.hexToRgb(clrString);
  var duration = Blockly.Arduino.valueToCode(this, 'DURATION',
          Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = objName + '.showBreath(' + index + ',' + val + ',' + color + ',' + duration + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xwkklightshow_showMeteor = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XRGBLed');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XRGBLed',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XRGBLed',port);
  }
  var arrObjs = [{type:'XRGBLed',port:port}];
  Blockly.Arduino.WKKit_addService('WKKLightShow', 'lgs', arrObjs);
  var objName = Blockly.Arduino.WKKit_getServiceName('WKKLightShow', 'lgs', arrObjs);
  //var val = Blockly.Arduino.valueToCode(block, 'VALUE',
  //        Blockly.Arduino.ORDER_NONE) || 0;
  var val = this.getFieldValue('VALUE');
  var clrString = this.getFieldValue('COLOR');
  var color = goog.color.hexToRgb(clrString);
  var duration = Blockly.Arduino.valueToCode(this, 'DURATION',
          Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = objName + '.showMeteor(' + val + ',' + color + ',' + duration + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xwkklightshow_clear = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XRGBLed');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XRGBLed',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XRGBLed',port);
  }
  var arrObjs = [{type:'XRGBLed',port:port}];
  Blockly.Arduino.WKKit_addService('WKKLightShow', 'lgs', arrObjs);
  var objName = Blockly.Arduino.WKKit_getServiceName('WKKLightShow', 'lgs', arrObjs);
  var index = this.getFieldValue('INDEX');
  var code = objName + '.clear(' + index + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xwkkaudioplayer_playTone = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XBuzzer');
  if (Blockly.Arduino.WKKit_isOnBoardModule('XBuzzer', port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XBuzzer', port);
  }
  var arrObjs = [{ type: 'XBuzzer', port: port }];
  Blockly.Arduino.WKKit_addService('WKKAudioPlayer', 'adp', arrObjs);
  var objName = Blockly.Arduino.WKKit_getServiceName('WKKAudioPlayer', 'adp', arrObjs);
  var frequency = Blockly.Arduino.valueToCode(this, 'FREQUENCY',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var duration = Blockly.Arduino.valueToCode(this, 'DURATION',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = objName + '.playTone(' + frequency + ', ' + duration + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xwkkaudioplayer_setNoteParameter = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XBuzzer');
  if (Blockly.Arduino.WKKit_isOnBoardModule('XBuzzer', port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XBuzzer', port);
  }
  var arrObjs = [{ type: 'XBuzzer', port: port }];
  Blockly.Arduino.WKKit_addService('WKKAudioPlayer', 'adp', arrObjs);
  var objName = Blockly.Arduino.WKKit_getServiceName('WKKAudioPlayer', 'adp', arrObjs);
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

Blockly.Arduino.wkkit_xwkkaudioplayer_playNote = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XBuzzer');
  if (Blockly.Arduino.WKKit_isOnBoardModule('XBuzzer', port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XBuzzer', port);
  }
  var arrObjs = [{ type: 'XBuzzer', port: port }];
  Blockly.Arduino.WKKit_addService('WKKAudioPlayer', 'adp', arrObjs);
  var objName = Blockly.Arduino.WKKit_getServiceName('WKKAudioPlayer', 'adp', arrObjs);
  var note = this.getFieldValue('NOTE');
  var scale = this.getFieldValue('SCALE');
  var tone = this.getFieldValue('TONE');
  var beat = this.getFieldValue('BEAT');
  var code = objName + '.playNote(' + note + ',' + scale + ',' + tone + ',' + beat + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xwkkaudioplayer_playMusic = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XBuzzer');
  if (Blockly.Arduino.WKKit_isOnBoardModule('XBuzzer', port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XBuzzer', port);
  }
  var arrObjs = [{ type: 'XBuzzer', port: port }];
  Blockly.Arduino.WKKit_addService('WKKAudioPlayer', 'adp', arrObjs);
  var objName = Blockly.Arduino.WKKit_getServiceName('WKKAudioPlayer', 'adp', arrObjs);
  var val = this.getFieldValue('VALUE');
  //var repeat = (block.getFieldValue('REPEAT') == 'TRUE') ? 1 : 0;
  var code = objName + '.playMusic(' + val/* + ',' + repeat*/ + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xwkkaudioplayer_playEffect = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XBuzzer');
  if (Blockly.Arduino.WKKit_isOnBoardModule('XBuzzer', port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XBuzzer', port);
  }
  var arrObjs = [{ type: 'XBuzzer', port: port }];
  Blockly.Arduino.WKKit_addService('WKKAudioPlayer', 'adp', arrObjs);
  var objName = Blockly.Arduino.WKKit_getServiceName('WKKAudioPlayer', 'adp', arrObjs);
  var effect = this.getFieldValue('EFFECT');
  var code = objName + '.playSound(' + effect + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xwkkaudioplayer_stop = function () {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XBuzzer');
  if (Blockly.Arduino.WKKit_isOnBoardModule('XBuzzer', port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XBuzzer', port);
  }
  var arrObjs = [{ type: 'XBuzzer', port: port }];
  Blockly.Arduino.WKKit_addService('WKKAudioPlayer', 'adp', arrObjs);
  var objName = Blockly.Arduino.WKKit_getServiceName('WKKAudioPlayer', 'adp', arrObjs);
  var code = objName + '.stop();\n';
  return code;
};

/********************************************
Communicator - 通信模块
*********************************************/

Blockly.Arduino.wkkit_xirreceiver_presskey = function() {
  var dropdown_press_key = this.getFieldValue('PRESSKEY');
var code = dropdown_press_key;
return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xirreceiver_enableLongPress = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XIRReceiver');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIRReceiver',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIRReceiver',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIRReceiver',port);
  // var val = Blockly.Arduino.valueToCode(this, 'VALUE',
  //     Blockly.Arduino.ORDER_NONE) || 0;
  var val = this.getFieldValue('PRESSKEY');
  var code = name + '.enableLongPress(' + val + ');\n';
  return code;
};

Blockly.Arduino.wkkit_xirreceiver_available = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XIRReceiver');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIRReceiver',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIRReceiver',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIRReceiver',port);
  var code = '(0xFF!=' + name + '.receive())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xirreceiver_receiveNumber = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XIRReceiver');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIRReceiver',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIRReceiver',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIRReceiver',port);
  // var val = Blockly.Arduino.valueToCode(this, 'VALUE',
  //     Blockly.Arduino.ORDER_NONE) || 0;
  var val = this.getFieldValue('PRESSKEY');
  var code = '(' + val + '==' + name + '.pick())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.wkkit_xirreceiver_waitMessage = function() {
  Blockly.Arduino.WKKit_addGlobal();
  var port = this.getFieldValue('XIRReceiver');
  if(Blockly.Arduino.WKKit_isOnBoardModule('XIRReceiver',port)) {
    Blockly.Arduino.WKKit_addOnBoardModule('XIRReceiver',port);
  }
  var name = Blockly.Arduino.WKKit_getModuleName('XIRReceiver',port);
  var code = name + '.wait();\n';
  return code;
};

/********************************************
System - 系统模块
*********************************************/
