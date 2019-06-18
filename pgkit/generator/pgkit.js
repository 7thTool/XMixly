'use strict';

goog.provide('Blockly.Arduino.pgkit');

goog.require('Blockly.Arduino');
goog.require('Blockly.JavaScript');

Blockly.Arduino.statementToCodeNoTab = function (block, name) {
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

Blockly.Arduino.addInclude = function (tag,code) {
  Blockly.Arduino.definitions_['define_' + tag] = code;
}

Blockly.Arduino.addDeclaration = function (tag, code) {
  Blockly.Arduino.definitions_['var_' + tag] = code;
}

Blockly.Arduino.addFunction = function (tag, code) {
  Blockly.Arduino.definitions_[tag] = code;
}

Blockly.Arduino.addSetup = function (tag, code) {
  Blockly.Arduino.setups_['setup_' + tag] = code;
}

Blockly.Arduino.addGlobal = function () {
  //只要使用了pgkit，强制添加pgkit全局代码
  Blockly.Arduino.addInclude('Arduino', '#include <Arduino.h>');
  Blockly.Arduino.addInclude('PGKSystem', '#include <PGKSystem.h>');
  Blockly.Arduino.addSetup('PGKSystem', 'XSystem.setup();');
}

Blockly.Arduino.addOnBoardModule = function (type, label) {
  Blockly.Arduino.addInclude(type, '#include <' + type + '.h>');
  var objName = label.toLowerCase();
  var globalCode = type + ' ' + objName + ';';
  Blockly.Arduino.addDeclaration(objName, globalCode);
  var setupCode = objName + '.setup(\"' + label + '\");';
  Blockly.Arduino.addSetup(objName, setupCode);
  //Blockly.Arduino.reservePort(label,objName);
}

Blockly.Arduino.isOnBoardModule = function (type, label) {
  if(type && label) {
      if(isNaN(label)) { //简单判断一下
          return true;
      }
  }
  return false;
}

Blockly.Arduino.getModuleName = function (type,port) {
  var name = "";
  var typeObj = window.PGKit.getTypeObj(type);
  if (typeObj) {
      if (typeObj.type == 'XIODriver') {
          name = ('io_' + port).toLowerCase();
      } else {
          if (Blockly.Arduino.isOnBoardModule(typeObj.type, port)) {
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
Blockly.Arduino.addService = function (type, n3c, objs) {
  Blockly.Arduino.addInclude(type, '#include <' + type + '.h>');
  var objName = n3c;
  for(var i=0;i<objs.length;i++) {
      objName += '_' + Blockly.Arduino.getModuleName(objs[i].type, objs[i].port);
  }
  var globalCode = type + ' ' + objName + ';';
  Blockly.Arduino.addDeclaration(objName, globalCode);
  var setupCode = objName + '.setup(';
  for(var i=0;i<objs.length;i++) {
      setupCode += '&' + Blockly.Arduino.getModuleName(objs[i].type, objs[i].port);
  }
  setupCode += ');';
  Blockly.Arduino.addSetup(objName, setupCode);
  //var loopCode = objName + '.loop();';
  //Blockly.Arduino.addLoop(objName, loopCode, true);
}

Blockly.Arduino.getServiceName = function (type, n3c, objs) {
  var objName = n3c;
  for(var i=0;i<objs.length;i++) {
      objName += '_' + Blockly.Arduino.getModuleName(objs[i].type, objs[i].port);
  }
  return objName;
}


/********************************************
Construct - 连接模块
*********************************************/

Blockly.Arduino.pgkit_construct_XPORTS = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('PORT');
  var type = this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  Blockly.Arduino.addInclude(type, '#include <' + type + '.h>');

  var objName = Blockly.Arduino.getModuleName(type,port);
  var globalCode = type + ' ' + objName + ';';
  Blockly.Arduino.addDeclaration(objName, globalCode);

  var setupCode = objName + '.setup(\"'
    + model
    + '\", \"'
    + port
    + '\");';
  Blockly.Arduino.addSetup(objName, setupCode);

  return '';
};

Blockly.Arduino.pgkit_xiodriver_digitalRead = function() {
  var port = this.getFieldValue('XIODriver');
  if(Blockly.Arduino.isOnBoardModule('XIODriver',port)) {
    Blockly.Arduino.addOnBoardModule('XIODriver',port);
  }
  var name = Blockly.Arduino.getModuleName('XIODriver',port);
  var index = this.getFieldValue('INDEX');
  var code = name + '.digitalRead(' + index + ')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xiodriver_analogRead = function() {
  var port = this.getFieldValue('XIODriver');
  if(Blockly.Arduino.isOnBoardModule('XIODriver',port)) {
    Blockly.Arduino.addOnBoardModule('XIODriver',port);
  }
  var name = Blockly.Arduino.getModuleName('XIODriver',port);
  var index = this.getFieldValue('INDEX');
  var code = name + '.analogRead(' + index + ')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xiodriver_digitalWrite = function () {
  var port = this.getFieldValue('XIODriver');
  if(Blockly.Arduino.isOnBoardModule('XIODriver',port)) {
    Blockly.Arduino.addOnBoardModule('XIODriver',port);
  }
  var name = Blockly.Arduino.getModuleName('XIODriver',port);
  var index = this.getFieldValue('INDEX');
  var value = this.getFieldValue('VALUE');
  var code = name + '.digitalWrite(' + index + ',' + value + ');\n';
  return code;
};

  // Led
  Blockly.Arduino.pgkit_led = function() {
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
  
Blockly.Arduino.pgkit_xservo_setAngle = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XServo');
  if(Blockly.Arduino.isOnBoardModule('XServo',port)) {
    Blockly.Arduino.addOnBoardModule('XServo',port);
  }
  var name = Blockly.Arduino.getModuleName('XServo',port);
  var angle = Blockly.Arduino.valueToCode(this, 'ANGLE',
          Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = name + '.setAngle(' + angle + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xservo_getAngle = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XServo');
  if(Blockly.Arduino.isOnBoardModule('XServo',port)) {
    Blockly.Arduino.addOnBoardModule('XServo',port);
  }
  var name = Blockly.Arduino.getModuleName('XServo',port);
  var code = name + '.getAngle()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xdualdcmotor_turn = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XDualDCMotor');
  if(Blockly.Arduino.isOnBoardModule('XDualDCMotor',port)) {
    Blockly.Arduino.addOnBoardModule('XDualDCMotor',port);
  }
  var name = Blockly.Arduino.getModuleName('XDualDCMotor',port);
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

Blockly.Arduino.pgkit_xdualdcmotor_stop = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XDualDCMotor');
  if(Blockly.Arduino.isOnBoardModule('XDualDCMotor',port)) {
    Blockly.Arduino.addOnBoardModule('XDualDCMotor',port);
  }
  var name = Blockly.Arduino.getModuleName('XDualDCMotor',port);
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

Blockly.Arduino.pgkit_xbutton_isPressed = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XButton');
  if(Blockly.Arduino.isOnBoardModule('XButton',port)) {
    Blockly.Arduino.addOnBoardModule('XButton',port);
  }
  var name = Blockly.Arduino.getModuleName('XButton',port);
  var code = name + '.isPressed()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xbutton_waitPressed = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XButton');
  if(Blockly.Arduino.isOnBoardModule('XButton',port)) {
    Blockly.Arduino.addOnBoardModule('XButton',port);
  }
  var name = Blockly.Arduino.getModuleName('XButton',port);
  var code = 'while(!' + name + '.isKnocked());\n';
  return code;
};

Blockly.Arduino.pgkit_xlightsensor_getLuminance = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XLightSensor');
  if(Blockly.Arduino.isOnBoardModule('XLightSensor',port)) {
    Blockly.Arduino.addOnBoardModule('XLightSensor',port);
  }
  var name = Blockly.Arduino.getModuleName('XLightSensor',port);
  var code = name + '.getLuminance()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xlightsensor_waitLuminance = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XLightSensor');
  if(Blockly.Arduino.isOnBoardModule('XLightSensor',port)) {
    Blockly.Arduino.addOnBoardModule('XLightSensor',port);
  }
  var name = Blockly.Arduino.getModuleName('XLightSensor',port);
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

Blockly.Arduino.pgkit_xsoundsensor_getVolume = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XSoundSensor');
  if(Blockly.Arduino.isOnBoardModule('XSoundSensor',port)) {
    Blockly.Arduino.addOnBoardModule('XSoundSensor',port);
  }
  var name = Blockly.Arduino.getModuleName('XSoundSensor',port);
  var code = name + '.getVolume()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xsoundsensor_waitVolume = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XSoundSensor');
  if(Blockly.Arduino.isOnBoardModule('XSoundSensor',port)) {
    Blockly.Arduino.addOnBoardModule('XSoundSensor',port);
  }
  var name = Blockly.Arduino.getModuleName('XSoundSensor',port);
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

Blockly.Arduino.pgkit_xirtracking_hasStatus = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XIRTracking');
  if(Blockly.Arduino.isOnBoardModule('XIRTracking',port)) {
    Blockly.Arduino.addOnBoardModule('XIRTracking',port);
  }
  var name = Blockly.Arduino.getModuleName('XIRTracking',port);
  var status = this.getFieldValue('STATUS');
  var code = '(' + status + '==' + name + '.getStatus())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xirtracking_waitStatus = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XIRTracking');
  if(Blockly.Arduino.isOnBoardModule('XIRTracking',port)) {
    Blockly.Arduino.addOnBoardModule('XIRTracking',port);
  }
  var name = Blockly.Arduino.getModuleName('XIRTracking',port);
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

Blockly.Arduino.pgkit_xirtracking6_hasStatus = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XIRTracking6');
  if(Blockly.Arduino.isOnBoardModule('XIRTracking6',port)) {
    Blockly.Arduino.addOnBoardModule('XIRTracking6',port);
  }
  var name = Blockly.Arduino.getModuleName('XIRTracking6',port);
  var status = this.getFieldValue('S1') | this.getFieldValue('S2') | this.getFieldValue('S3') 
  | this.getFieldValue('S4') | this.getFieldValue('S5') | this.getFieldValue('S6');
  var code = '(' + status + '==' + name + '.getStatus())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xirtracking6_waitStatus = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XIRTracking6');
  if(Blockly.Arduino.isOnBoardModule('XIRTracking6',port)) {
    Blockly.Arduino.addOnBoardModule('XIRTracking6',port);
  }
  var name = Blockly.Arduino.getModuleName('XIRTracking6',port);
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

Blockly.Arduino.pgkit_xultrasonic_getDistance = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XUltrasonic');
  if(Blockly.Arduino.isOnBoardModule('XUltrasonic',port)) {
    Blockly.Arduino.addOnBoardModule('XUltrasonic',port);
  }
  var name = Blockly.Arduino.getModuleName('XUltrasonic',port);
  var code = '(' + name + '.getDistance()/10)';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xultrasonic_waitDistance = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XUltrasonic');
  if(Blockly.Arduino.isOnBoardModule('XUltrasonic',port)) {
    Blockly.Arduino.addOnBoardModule('XUltrasonic',port);
  }
  var name = Blockly.Arduino.getModuleName('XUltrasonic',port);
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

Blockly.Arduino.pgkit_xiravoiding_start = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XIRAvoiding');
  if(Blockly.Arduino.isOnBoardModule('XIRAvoiding',port)) {
    Blockly.Arduino.addOnBoardModule('XIRAvoiding',port);
  }
  var name = Blockly.Arduino.getModuleName('XIRAvoiding',port);
  var sensitive = Blockly.Arduino.valueToCode(this, 'SENSITIVE',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.start(' + sensitive + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xiravoiding_stop = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XIRAvoiding');
  if(Blockly.Arduino.isOnBoardModule('XIRAvoiding',port)) {
    Blockly.Arduino.addOnBoardModule('XIRAvoiding',port);
  }
  var name = Blockly.Arduino.getModuleName('XIRAvoiding',port);
  var code = name + '.stop();\n';
  return code;
};

Blockly.Arduino.pgkit_xiravoiding_getStatus = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XIRAvoiding');
  if(Blockly.Arduino.isOnBoardModule('XIRAvoiding',port)) {
    Blockly.Arduino.addOnBoardModule('XIRAvoiding',port);
  }
  var name = Blockly.Arduino.getModuleName('XIRAvoiding',port);
  var code = '(' + name + '.getStatus()==1)';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xiravoiding_waitStatus = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XIRAvoiding');
  if(Blockly.Arduino.isOnBoardModule('XIRAvoiding',port)) {
    Blockly.Arduino.addOnBoardModule('XIRAvoiding',port);
  }
  var name = Blockly.Arduino.getModuleName('XIRAvoiding',port);
  var event = this.getFieldValue('EVENT');
  var code;
  if(event==1) {
    code = 'while(' + name + '.getStatus()!=1);\n';
  } else {
    code = 'while(' + name + '.getStatus()==1);\n';
  }
  return code;
};

Blockly.Arduino.pgkit_xpotentiometer_getValue = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XPotentiometer');
  if(Blockly.Arduino.isOnBoardModule('XPotentiometer',port)) {
    Blockly.Arduino.addOnBoardModule('XPotentiometer',port);
  }
  var name = Blockly.Arduino.getModuleName('XPotentiometer',port);
  var code = name + '.getValue()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xpotentiometer_waitValue = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XPotentiometer');
  if(Blockly.Arduino.isOnBoardModule('XPotentiometer',port)) {
    Blockly.Arduino.addOnBoardModule('XPotentiometer',port);
  }
  var name = Blockly.Arduino.getModuleName('XPotentiometer',port);
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

Blockly.Arduino.pgkit_xhumiture_getHumidity = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XHumiture');
  if(Blockly.Arduino.isOnBoardModule('XHumiture',port)) {
    Blockly.Arduino.addOnBoardModule('XHumiture',port);
  }
  var name = Blockly.Arduino.getModuleName('XHumiture',port);
  var code = name + '.getHumidity()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xhumiture_getTemperature = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XHumiture');
  if(Blockly.Arduino.isOnBoardModule('XHumiture',port)) {
    Blockly.Arduino.addOnBoardModule('XHumiture',port);
  }
  var name = Blockly.Arduino.getModuleName('XHumiture',port);
  var code = name + '.getTemperature()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xhumiture_waitHumidity = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XHumiture');
  if(Blockly.Arduino.isOnBoardModule('XHumiture',port)) {
    Blockly.Arduino.addOnBoardModule('XHumiture',port);
  }
  var name = Blockly.Arduino.getModuleName('XHumiture',port);
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

Blockly.Arduino.pgkit_xhumiture_waitTemperature = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XHumiture');
  if(Blockly.Arduino.isOnBoardModule('XHumiture',port)) {
    Blockly.Arduino.addOnBoardModule('XHumiture',port);
  }
  var name = Blockly.Arduino.getModuleName('XHumiture',port);
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

Blockly.Arduino.pgkit_xpir_isMotionDetected = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XPIR');
  if(Blockly.Arduino.isOnBoardModule('XPIR',port)) {
    Blockly.Arduino.addOnBoardModule('XPIR',port);
  }
  var name = Blockly.Arduino.getModuleName('XPIR',port);
  var code = name + '.isHumanMotionDetected()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xpir_waitMotion = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XPIR');
  if(Blockly.Arduino.isOnBoardModule('XPIR',port)) {
    Blockly.Arduino.addOnBoardModule('XPIR',port);
  }
  var name = Blockly.Arduino.getModuleName('XPIR',port);
  var event = this.getFieldValue('INDEX');
  var code = '';
  if(event==1) {
    code = 'while(!(' + name + '.isHumanMotionDetected()));\n';
  } else {
    code = 'while(' + name + '.isHumanMotionDetected());\n';
  }
  return code;
};

Blockly.Arduino.pgkit_xshocksensor_isShocking = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XShockSensor');
  if(Blockly.Arduino.isOnBoardModule('XShockSensor',port)) {
    Blockly.Arduino.addOnBoardModule('XShockSensor',port);
  }
  var name = Blockly.Arduino.getModuleName('XShockSensor',port);
  var code = '(' + name + '.isShocking()==1)';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xshocksensor_waitStatus = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XShockSensor');
  if(Blockly.Arduino.isOnBoardModule('XShockSensor',port)) {
    Blockly.Arduino.addOnBoardModule('XShockSensor',port);
  }
  var name = Blockly.Arduino.getModuleName('XShockSensor',port);
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

Blockly.Arduino.pgkit_xsegdisplay_showNumber = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XSegDisplay');
  if(Blockly.Arduino.isOnBoardModule('XSegDisplay',port)) {
    Blockly.Arduino.addOnBoardModule('XSegDisplay',port);
  }
  var name = Blockly.Arduino.getModuleName('XSegDisplay',port);
  var number = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = name + '.showNumber((float)' + number + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xsegdisplay_showNumberEx = function() {
  Blockly.Arduino.addGlobal();
var port = this.getFieldValue('XSegDisplay');
if(Blockly.Arduino.isOnBoardModule('XSegDisplay',port)) {
  Blockly.Arduino.addOnBoardModule('XSegDisplay',port);
}
var name = Blockly.Arduino.getModuleName('XSegDisplay',port);
var number = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_ATOMIC) || 0;
var format = this.getFieldValue('FORMAT');
var code = name + '.showNumber((uint32_t)' + number + ',' + format + ');\n';
return code;
};

Blockly.Arduino.pgkit_xsegdisplay_showCharacter = function() {
  Blockly.Arduino.addGlobal();
var port = this.getFieldValue('XSegDisplay');
if(Blockly.Arduino.isOnBoardModule('XSegDisplay',port)) {
  Blockly.Arduino.addOnBoardModule('XSegDisplay',port);
}
var name = Blockly.Arduino.getModuleName('XSegDisplay',port);
var index = this.getFieldValue('INDEX');
var number = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_ATOMIC) || 0;
var code = name + '.showCharacter(' + index + ',' + number + ');\n';
return code;
};

Blockly.Arduino.pgkit_xsegdisplay_showSegment = function() {
  Blockly.Arduino.addGlobal();
var port = this.getFieldValue('XSegDisplay');
if(Blockly.Arduino.isOnBoardModule('XSegDisplay',port)) {
  Blockly.Arduino.addOnBoardModule('XSegDisplay',port);
}
var name = Blockly.Arduino.getModuleName('XSegDisplay',port);
var index = this.getFieldValue('INDEX');
var segment = this.getFieldValue('VALUE');
var code = name + '.showSegment(' + index + ',\'' + segment + '\');\n';
return code;
};

Blockly.Arduino.pgkit_xsegdisplay_clearSegment = function() {
  Blockly.Arduino.addGlobal();
var port = this.getFieldValue('XSegDisplay');
if(Blockly.Arduino.isOnBoardModule('XSegDisplay',port)) {
  Blockly.Arduino.addOnBoardModule('XSegDisplay',port);
}
var name = Blockly.Arduino.getModuleName('XSegDisplay',port);
var index = this.getFieldValue('INDEX');
var segment = this.getFieldValue('VALUE');
var code = name + '.clearSegment(' + index + ',\'' + segment + '\');\n';
return code;
};

Blockly.Arduino.pgkit_xsegdisplay_clear = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XSegDisplay');
  if(Blockly.Arduino.isOnBoardModule('XSegDisplay',port)) {
    Blockly.Arduino.addOnBoardModule('XSegDisplay',port);
  }
  var name = Blockly.Arduino.getModuleName('XSegDisplay',port);
  var index = this.getFieldValue('INDEX');
  var code = name + '.clear(' + index + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xledmatrix_move = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.getModuleName('XLEDMatrix',port);
  var x = Blockly.Arduino.valueToCode(this, 'X',
    Blockly.Arduino.ORDER_NONE) || 0;
  var y = Blockly.Arduino.valueToCode(this, 'Y',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.move(' + x + ',' + y + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xledmatrix_setBrightness = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.getModuleName('XLEDMatrix',port);
  var val = this.getFieldValue('VALUE');
  var code = name + '.setBrightness(' + val + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xledmatrix_setColorInverse = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.getModuleName('XLEDMatrix',port);
  var val = this.getFieldValue('VALUE');
  var code = name + '.setColorInverse(' + val + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xledmatrix_setEffect = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.getModuleName('XLEDMatrix',port);
  var effect = this.getFieldValue('EFFECT');
  var speed = this.getFieldValue('SPEED');
  var code = name + '.setEffect(' + effect + ',' + speed + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xledmatrix_showNumber = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.getModuleName('XLEDMatrix',port);
  var num = Blockly.Arduino.valueToCode(this, 'NUM',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.showNumber(' + num + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xledmatrix_showNumberPair = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.getModuleName('XLEDMatrix',port);
  var a = Blockly.Arduino.valueToCode(this, 'A',
    Blockly.Arduino.ORDER_NONE) || 0;
  var b = Blockly.Arduino.valueToCode(this, 'B',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.showNumberPair(' + a + ',' + b + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xledmatrix_showString = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.getModuleName('XLEDMatrix',port);
  var val = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_NONE) || '';
  var code = name + '.showString(' + val + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xledmatrix_showEmoticon = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.getModuleName('XLEDMatrix',port);
  var emot = this.getFieldValue('EMOTION');
  var code = name + '.showEmoticon(' + emot + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xledmatrix_showFlag = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.getModuleName('XLEDMatrix',port);
  var index = this.getFieldValue('INDEX');
  var value = this.getFieldValue('VALUE');
  var code = name + '.showFlag(' + value + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xledmatrix_clear = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XLEDMatrix');
  if(Blockly.Arduino.isOnBoardModule('XLEDMatrix',port)) {
    Blockly.Arduino.addOnBoardModule('XLEDMatrix',port);
  }
  var name = Blockly.Arduino.getModuleName('XLEDMatrix',port);
  var code = name + '.clear();\n';
  return code;
};

Blockly.Arduino.pgkit_xvoicebroadcast_reportObject = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.getModuleName('XVoiceBroadcast',port);
  var index = this.getFieldValue('INDEX');
  var value = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_NONE) || 0;
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportObject(' + index + ',' + value + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xvoicebroadcast_reportTime = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.getModuleName('XVoiceBroadcast',port);
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

Blockly.Arduino.pgkit_xvoicebroadcast_reportDate = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.getModuleName('XVoiceBroadcast',port);
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

Blockly.Arduino.pgkit_xvoicebroadcast_reportOperator = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.getModuleName('XVoiceBroadcast',port);
  var index = this.getFieldValue('INDEX');
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportOperator(' + index + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xvoicebroadcast_reportSound = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.getModuleName('XVoiceBroadcast',port);
  //var index = this.getFieldValue('INDEX');
  var value = this.getFieldValue('VALUE');
  var repeat = (this.getFieldValue('REPEAT') == 'TRUE') ? 1 : 0;
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportSound(' + value + ',' + repeat + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xvoicebroadcast_stop = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.getModuleName('XVoiceBroadcast',port);
  // TODO: Assemble Arduino into code variable.
  var code = name + '.stop();\n';
  return code;
};

Blockly.Arduino.pgkit_xvoicebroadcast_isPlaying = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XVoiceBroadcast');
  if(Blockly.Arduino.isOnBoardModule('XVoiceBroadcast',port)) {
    Blockly.Arduino.addOnBoardModule('XVoiceBroadcast',port);
  }
  var name = Blockly.Arduino.getModuleName('XVoiceBroadcast',port);
  var code = name + '.isPlaying()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xpgklightshow_showColor = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XRGBLed');
  if(Blockly.Arduino.isOnBoardModule('XRGBLed',port)) {
    Blockly.Arduino.addOnBoardModule('XRGBLed',port);
  }
  var arrObjs = [{type:'XRGBLed',port:port}];
  Blockly.Arduino.addService('PGKLightShow', 'lgs', arrObjs);
  var objName = Blockly.Arduino.getServiceName('PGKLightShow', 'lgs', arrObjs);
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

Blockly.Arduino.pgkit_xpgklightshow_showRGB = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XRGBLed');
  if(Blockly.Arduino.isOnBoardModule('XRGBLed',port)) {
    Blockly.Arduino.addOnBoardModule('XRGBLed',port);
  }
  var arrObjs = [{type:'XRGBLed',port:port}];
  Blockly.Arduino.addService('PGKLightShow', 'lgs', arrObjs);
  var objName = Blockly.Arduino.getServiceName('PGKLightShow', 'lgs', arrObjs);
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

Blockly.Arduino.pgkit_xpgklightshow_clear = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XRGBLed');
  if(Blockly.Arduino.isOnBoardModule('XRGBLed',port)) {
    Blockly.Arduino.addOnBoardModule('XRGBLed',port);
  }
  var arrObjs = [{type:'XRGBLed',port:port}];
  Blockly.Arduino.addService('PGKLightShow', 'lgs', arrObjs);
  var objName = Blockly.Arduino.getServiceName('PGKLightShow', 'lgs', arrObjs);
  var index = this.getFieldValue('INDEX');
  var code = objName + '.clear(' + index + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xpgkaudioplayer_playTone = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XBuzzer');
  if (Blockly.Arduino.isOnBoardModule('XBuzzer', port)) {
    Blockly.Arduino.addOnBoardModule('XBuzzer', port);
  }
  var arrObjs = [{ type: 'XBuzzer', port: port }];
  Blockly.Arduino.addService('PGKAudioPlayer', 'adp', arrObjs);
  var objName = Blockly.Arduino.getServiceName('PGKAudioPlayer', 'adp', arrObjs);
  var frequency = Blockly.Arduino.valueToCode(this, 'FREQUENCY',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var duration = Blockly.Arduino.valueToCode(this, 'DURATION',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = objName + '.playTone(' + frequency + ', ' + duration + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xpgkaudioplayer_setNoteParameter = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XBuzzer');
  if (Blockly.Arduino.isOnBoardModule('XBuzzer', port)) {
    Blockly.Arduino.addOnBoardModule('XBuzzer', port);
  }
  var arrObjs = [{ type: 'XBuzzer', port: port }];
  Blockly.Arduino.addService('PGKAudioPlayer', 'adp', arrObjs);
  var objName = Blockly.Arduino.getServiceName('PGKAudioPlayer', 'adp', arrObjs);
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

Blockly.Arduino.pgkit_xpgkaudioplayer_playNote = function () {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XBuzzer');
  if (Blockly.Arduino.isOnBoardModule('XBuzzer', port)) {
    Blockly.Arduino.addOnBoardModule('XBuzzer', port);
  }
  var arrObjs = [{ type: 'XBuzzer', port: port }];
  Blockly.Arduino.addService('PGKAudioPlayer', 'adp', arrObjs);
  var objName = Blockly.Arduino.getServiceName('PGKAudioPlayer', 'adp', arrObjs);
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

Blockly.Arduino.pgkit_xirreceiver_enableLongPress = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XIRReceiver');
  if(Blockly.Arduino.isOnBoardModule('XIRReceiver',port)) {
    Blockly.Arduino.addOnBoardModule('XIRReceiver',port);
  }
  var name = Blockly.Arduino.getModuleName('XIRReceiver',port);
  var val = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.enableLongPress(' + val + ');\n';
  return code;
};

Blockly.Arduino.pgkit_xirreceiver_available = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XIRReceiver');
  if(Blockly.Arduino.isOnBoardModule('XIRReceiver',port)) {
    Blockly.Arduino.addOnBoardModule('XIRReceiver',port);
  }
  var name = Blockly.Arduino.getModuleName('XIRReceiver',port);
  var code = '(0xFF!=' + name + '.receive())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xirreceiver_receiveNumber = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XIRReceiver');
  if(Blockly.Arduino.isOnBoardModule('XIRReceiver',port)) {
    Blockly.Arduino.addOnBoardModule('XIRReceiver',port);
  }
  var name = Blockly.Arduino.getModuleName('XIRReceiver',port);
  var val = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_NONE) || 0;
  var code = '(' + val + '==' + name + '.pick())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.pgkit_xirreceiver_waitMessage = function() {
  Blockly.Arduino.addGlobal();
  var port = this.getFieldValue('XIRReceiver');
  if(Blockly.Arduino.isOnBoardModule('XIRReceiver',port)) {
    Blockly.Arduino.addOnBoardModule('XIRReceiver',port);
  }
  var name = Blockly.Arduino.getModuleName('XIRReceiver',port);
  var code = name + '.wait();\n';
  return code;
};

/********************************************
System - 系统模块
*********************************************/
