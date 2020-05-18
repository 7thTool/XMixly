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

// Blockly.Arduino.XBlockly_addOnBoardModule = function (type, label) {
//   Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');
//   var objName = label;//.toLowerCase();
//   var globalCode = type + ' ' + objName + ';';
//   Blockly.Arduino.XBlockly_addDeclaration(objName, globalCode);
//   var setupCode = objName + '.setup(\"' + label + '\");';
//   Blockly.Arduino.XBlockly_addSetup(objName, setupCode);
//   //Blockly.Arduino.reservePort(label,objName);
//   return objName;
// }

// Blockly.Arduino.XBlockly_isOnBoardModule = function (type, label) {
//   if(type && label) {
//       var obj = window.XBlockly.getObjByTypeId(type,label);
//       return window.XBlockly.IsOnBoardObj(obj);
//   }
//   return false;
// }

Blockly.Arduino.XBlockly_addService = function (type, n3c, objs) {
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');
  var objName = n3c;
  for(var i=0;i<objs.length;i++) {
      objName += '_' + objs[i];
  }
  var globalCode = type + ' ' + objName + ';';
  Blockly.Arduino.XBlockly_addDeclaration(objName, globalCode);
  var setupCode = objName + '.setup(';
  for(var i=0;i<objs.length;i++) {
      setupCode += '&' + objs[i];
  }
  setupCode += ');';
  Blockly.Arduino.XBlockly_addSetup(objName, setupCode);
  //var loopCode = objName + '.loop();';
  //Blockly.Arduino.addLoop(objName, loopCode, true);
  return objName;
}

/********************************************
Construct - 连接模块
*********************************************/

Blockly.Arduino.xblockly_construct_INIT = function() {
  var main_board = this.getFieldValue('XMainBoard');
  if(window.XBlockly.MainBoard != main_board) {
    window.XBlockly.MainBoard = main_board;
    // var jsonObjects = '{"modules":[]}';
    // window.XBlockly.init(JSON.parse(jsonObjects));
  }
  window.XBlockly.resetAllObjs();
  switch(main_board)
  {
    case 'Arduino/PanGu': {
      Blockly.Arduino.XBlockly_addInclude('Arduino', '#include <Arduino.h>');
      //Blockly.Arduino.XBlockly_addInclude('XMainBoard', '#include <Pangu.h>');
      Blockly.Arduino.XBlockly_addInclude('XSystem', '#include <XPGSystem.h>');
      Blockly.Arduino.XBlockly_addSetup('XSystem', 'XSystem.setup();');
    }
    break;
    case 'Arduino/WuKong': {
      Blockly.Arduino.XBlockly_addInclude('Arduino', '#include <Arduino.h>');
      //Blockly.Arduino.XBlockly_addInclude('XMainBoard', '#include <Wukong.h>');
      Blockly.Arduino.XBlockly_addInclude('XSystem', '#include <XWKSystem.h>');
      Blockly.Arduino.XBlockly_addSetup('XSystem', 'XSystem.setup();');
    }
    break;
    default: {
    }
    break;
  }
  return '';
};

Blockly.Arduino.xblockly_construct_XPORTS = function () {
  var name = this.getFieldValue('VAR');
  var port = this.getFieldValue('PORT');
  var type = this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,'p'+port);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", \"'
    + port
    + '\");';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_construct_ONBOARD = function () {
  var name = this.getFieldValue('VAR');
  var type = this.getFieldValue('TYPE');
  var label = this.getFieldValue('LABEL');
  
  window.XBlockly.addOrUpdateObj(type,name,label);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + label
    + '\");';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xbutton_INIT = function () {
  var name = this.getFieldValue('VAR');
  var pin = this.getFieldValue('PIN');
  var type = 'XButton';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,pin);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + pin
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xbuzzer_INIT = function () {
  var name = this.getFieldValue('VAR');
  var pin = this.getFieldValue('PIN');
  var type = 'XBuzzer';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,pin);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + pin
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xdualdcmotor_INIT = function () {
  var name = this.getFieldValue('VAR');
  var sda = this.getFieldValue('SDA');
  var scl = this.getFieldValue('SCL');
  var rst = this.getFieldValue('RST');
  var sel = this.getFieldValue('SEL');
  var type = 'XDualDCMotor';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,sda+'_'+scl+'_'+rst+'_'+sel);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + sda
    + ', '
    + scl
    + ', '
    + rst
    + ', '
    + sel
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xhumiture_INIT = function () {
  var name = this.getFieldValue('VAR');
  var pin = this.getFieldValue('PIN');
  var type = 'XHumiture';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,pin);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + pin
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xiravoiding_INIT = function () {
  var name = this.getFieldValue('VAR');
  var ctl = this.getFieldValue('CTL');
  var sta = this.getFieldValue('STA');
  var type = 'XIRAvoiding';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,ctl+'_'+sta);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + ctl
    + ', '
    + sta
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xirreceiver_INIT = function () {
  var name = this.getFieldValue('VAR');
  var sta = this.getFieldValue('STA');
  var dat = this.getFieldValue('DAT');
  var type = 'XIRReceiver';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,sta+'_'+dat);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + sta
    + ', '
    + dat
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xirtracking_INIT = function () {
  var name = this.getFieldValue('VAR');
  var s1 = this.getFieldValue('S1');
  var s2 = this.getFieldValue('S2');
  var type = 'XIRTracking';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,s1+'_'+s2);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + s1
    + ', '
    + s2
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xirtracking6_INIT = function () {
  var name = this.getFieldValue('VAR');
  var sda = this.getFieldValue('SDA');
  var scl = this.getFieldValue('SCL');
  var rst = this.getFieldValue('RST');
  var sel = this.getFieldValue('SEL');
  var type = 'XIRTracking66';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,sda+'_'+scl+'_'+rst+'_'+sel);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + sda
    + ', '
    + scl
    + ', '
    + rst
    + ', '
    + sel
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xledmatrix_INIT = function () {
  var name = this.getFieldValue('VAR');
  var sda = this.getFieldValue('SDA');
  var scl = this.getFieldValue('SCL');
  var rst = this.getFieldValue('RST');
  var sel = this.getFieldValue('SEL');
  var type = 'XLEDMatrix';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,sda+'_'+scl+'_'+rst+'_'+sel);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + sda
    + ', '
    + scl
    + ', '
    + rst
    + ', '
    + sel
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xlightsensor_INIT = function () {
  var name = this.getFieldValue('VAR');
  var pin = this.getFieldValue('PIN');
  var type = 'XLightSensor';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,pin);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + pin
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xsoundsensor_INIT = function () {
  var name = this.getFieldValue('VAR');
  var pin = this.getFieldValue('PIN');
  var type = 'XSoundSensor';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,pin);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + pin
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xpir_INIT = function () {
  var name = this.getFieldValue('VAR');
  var pin = this.getFieldValue('PIN');
  var type = 'XPIR';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,pin);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + pin
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xpotentiometer_INIT = function () {
  var name = this.getFieldValue('VAR');
  var pin = this.getFieldValue('PIN');
  var type = 'XPotentiometer';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,pin);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + pin
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xrgbled_INIT = function () {
  var name = this.getFieldValue('VAR');
  var pin = this.getFieldValue('PIN');
  var type = 'XRGBLed';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,pin);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + pin
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xsegdisplay_INIT = function () {
  var name = this.getFieldValue('VAR');
  var dat = this.getFieldValue('DAT');
  var clk = this.getFieldValue('CLK');
  var type = 'XIRTracking';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,dat+'_'+clk);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + dat
    + ', '
    + clk
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xservo_INIT = function () {
  var name = this.getFieldValue('VAR');
  var pin = this.getFieldValue('PIN');
  var type = 'XServo';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,pin);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + pin
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xultrasonic_INIT = function () {
  var name = this.getFieldValue('VAR');
  var trig = this.getFieldValue('TRIG');
  var echo = this.getFieldValue('ECHO');
  var type = 'XUltrasonic';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,trig+'_'+echo);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + trig
    + ', '
    + echo
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xvoicebroadcast_INIT = function () {
  var name = this.getFieldValue('VAR');
  var sda = this.getFieldValue('SDA');
  var scl = this.getFieldValue('SCL');
  var rst = this.getFieldValue('RST');
  var sel = this.getFieldValue('SEL');
  var type = 'XVoiceBroadcast';//this.getFieldValue('TYPE');
  var model = this.getFieldValue('MODEL');
  
  window.XBlockly.addOrUpdateObj(type,name,sda+'_'+scl+'_'+rst+'_'+sel);
  Blockly.Arduino.XBlockly_addInclude(type, '#include <' + type + '.h>');

  var globalCode = type + ' ' + name + ';';
  Blockly.Arduino.XBlockly_addDeclaration(name, globalCode);

  var setupCode = name + '.setup(\"'
    + model
    + '\", '
    + sda
    + ', '
    + scl
    + ', '
    + rst
    + ', '
    + sel
    + ');';
  Blockly.Arduino.XBlockly_addSetup(name, setupCode);

  return '';
};

Blockly.Arduino.xblockly_xiodriver_digitalRead = function() {
  var name = this.getFieldValue('XIODriver');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIODriver', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIODriver', name);
  // }
  var index = this.getFieldValue('INDEX');
  var code = name + '.digitalRead(' + index + ')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xiodriver_analogRead = function() {
  var name = this.getFieldValue('XIODriver');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIODriver', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIODriver', name);
  // }
  var index = this.getFieldValue('INDEX');
  var code = name + '.analogRead(' + index + ')';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xiodriver_digitalWrite = function () {
  var name = this.getFieldValue('XIODriver');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIODriver', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIODriver', name);
  // }
  var index = this.getFieldValue('INDEX');
  var value = this.getFieldValue('VALUE');
  var code = name + '.digitalWrite(' + index + ',' + value + ');\n';
  return code;
};


/********************************************
Move - 运动模块
*********************************************/
  
Blockly.Arduino.xblockly_xservo_setAngle = function() {
  var name = this.getFieldValue('XServo');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XServo', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XServo', name);
  // }
  var angle = Blockly.Arduino.valueToCode(this, 'ANGLE',
          Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = name + '.setAngle(' + angle + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xservo_getAngle = function() {
  var name = this.getFieldValue('XServo');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XServo', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XServo', name);
  // }
  var code = name + '.getAngle()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xdualdcmotor_turn = function() {
  var name = this.getFieldValue('XDualDCMotor');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XDualDCMotor', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XDualDCMotor', name);
  // }
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
  var name = this.getFieldValue('XDualDCMotor');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XDualDCMotor', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XDualDCMotor', name);
  // }
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
  var name = this.getFieldValue('XButton');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XButton', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XButton', name);
  // }
  var code = name + '.isPressed()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xbutton_waitPressed = function() {
  var name = this.getFieldValue('XButton');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XButton', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XButton', name);
  // }
  var code = 'while(!' + name + '.isKnocked());\n';
  return code;
};

Blockly.Arduino.xblockly_xlightsensor_getLuminance = function() {
  var name = this.getFieldValue('XLightSensor');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLightSensor', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLightSensor', name);
  // }
  var code = name + '.getLuminance()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xlightsensor_waitLuminance = function() {
  var name = this.getFieldValue('XLightSensor');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLightSensor', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLightSensor', name);
  // }
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
  var name = this.getFieldValue('XSoundSensor');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XSoundSensor', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XSoundSensor', name);
  // }
  var code = name + '.getVolume()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xsoundsensor_waitVolume = function () {
  var name = this.getFieldValue('XSoundSensor');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XSoundSensor', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XSoundSensor', name);
  // }
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
  var name = this.getFieldValue('XIRTracking');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRTracking', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIRTracking', name);
  // }
  var status = this.getFieldValue('STATUS');
  var code = '(' + status + '==' + name + '.getStatus())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xirtracking_waitStatus = function () {
  var name = this.getFieldValue('XIRTracking');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRTracking', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIRTracking', name);
  // }
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
  var name = this.getFieldValue('XIRTracking6');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRTracking6', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIRTracking6', name);
  // }
  var status = this.getFieldValue('S1') | this.getFieldValue('S2') | this.getFieldValue('S3') 
  | this.getFieldValue('S4') | this.getFieldValue('S5') | this.getFieldValue('S6');
  var code = '(' + status + '==' + name + '.getStatus())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xirtracking6_waitStatus = function () {
  var name = this.getFieldValue('XIRTracking6');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRTracking6', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIRTracking6', name);
  // }
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
  var name = this.getFieldValue('XUltrasonic');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XUltrasonic', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XUltrasonic', name);
  // }
  var code = '(' + name + '.getDistance()/10)';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xultrasonic_waitDistance = function() {
  var name = this.getFieldValue('XUltrasonic');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XUltrasonic', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XUltrasonic', name);
  // }
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
  var name = this.getFieldValue('XIRAvoiding');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRAvoiding', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIRAvoiding', name);
  // }
  var sensitive = Blockly.Arduino.valueToCode(this, 'SENSITIVE',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.start(' + sensitive + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xiravoiding_stop = function () {
  var name = this.getFieldValue('XIRAvoiding');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRAvoiding', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIRAvoiding', name);
  // }
  var code = name + '.stop();\n';
  return code;
};

Blockly.Arduino.xblockly_xiravoiding_getStatus = function() {
  var name = this.getFieldValue('XIRAvoiding');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRAvoiding', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIRAvoiding', name);
  // }
  var code = '(' + name + '.getStatus()==1)';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xiravoiding_waitStatus = function () {
  var name = this.getFieldValue('XIRAvoiding');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRAvoiding', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIRAvoiding', name);
  // }
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
  var name = this.getFieldValue('XPotentiometer');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XPotentiometer', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XPotentiometer', name);
  // }
  var code = name + '.getValue()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xpotentiometer_waitValue = function () {
  var name = this.getFieldValue('XPotentiometer');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XPotentiometer', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XPotentiometer', name);
  // }
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
  var name = this.getFieldValue('XHumiture');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XHumiture', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XHumiture', name);
  // }
  var code = name + '.getHumidity()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xhumiture_getTemperature = function() {
  var name = this.getFieldValue('XHumiture');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XHumiture', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XHumiture', name);
  // }
  var code = name + '.getTemperature()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xhumiture_waitHumidity = function() {
  var name = this.getFieldValue('XHumiture');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XHumiture', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XHumiture', name);
  // }
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
  var name = this.getFieldValue('XHumiture');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XHumiture', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XHumiture', name);
  // }
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
  var name = this.getFieldValue('XPIR');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XPIR', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XPIR', name);
  // }
  var code = name + '.isHumanMotionDetected()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xpir_waitMotion = function() {
  var name = this.getFieldValue('XPIR');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XPIR', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XPIR', name);
  // }
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
  var name = this.getFieldValue('XShockSensor');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XShockSensor', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XShockSensor', name);
  // }
  var code = '(' + name + '.isShocking()==1)';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xshocksensor_waitStatus = function () {
  var name = this.getFieldValue('XShockSensor');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XShockSensor', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XShockSensor', name);
  // }
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
  var name = this.getFieldValue('XSegDisplay');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XSegDisplay', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XSegDisplay', name);
  // }
  var number = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = name + '.showNumber((float)' + number + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xsegdisplay_showNumberEx = function() {
  var name = this.getFieldValue('XSegDisplay');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XSegDisplay', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XSegDisplay', name);
  // }
  var number = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var format = this.getFieldValue('FORMAT');
  var code = name + '.showNumber((uint32_t)' + number + ',' + format + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xsegdisplay_showCharacter = function() {
  var name = this.getFieldValue('XSegDisplay');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XSegDisplay', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XSegDisplay', name);
  // }
  var index = this.getFieldValue('INDEX');
  var number = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = name + '.showCharacter(' + index + ',' + number + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xsegdisplay_showSegment = function() {
  var name = this.getFieldValue('XSegDisplay');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XSegDisplay', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XSegDisplay', name);
  // }
  var index = this.getFieldValue('INDEX');
  var segment = this.getFieldValue('VALUE');
  var code = name + '.showSegment(' + index + ',\'' + segment + '\');\n';
  return code;
};

Blockly.Arduino.xblockly_xsegdisplay_clearSegment = function() {
  var name = this.getFieldValue('XSegDisplay');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XSegDisplay', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XSegDisplay', name);
  // }
  var index = this.getFieldValue('INDEX');
  var segment = this.getFieldValue('VALUE');
  var code = name + '.clearSegment(' + index + ',\'' + segment + '\');\n';
  return code;
};

Blockly.Arduino.xblockly_xsegdisplay_clear = function() {
  var name = this.getFieldValue('XSegDisplay');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XSegDisplay', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XSegDisplay', name);
  // }
  var index = this.getFieldValue('INDEX');
  var code = name + '.clear(' + index + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_move = function () {
  var name = this.getFieldValue('XLEDMatrix');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix', name);
  // }
  var x = Blockly.Arduino.valueToCode(this, 'X',
    Blockly.Arduino.ORDER_NONE) || 0;
  var y = Blockly.Arduino.valueToCode(this, 'Y',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.move(' + x + ',' + y + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_setBrightness = function () {
  var name = this.getFieldValue('XLEDMatrix');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix', name);
  // }
  var val = this.getFieldValue('VALUE');
  var code = name + '.setBrightness(' + val + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_setColorInverse = function () {
  var name = this.getFieldValue('XLEDMatrix');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix', name);
  // }
  var val = this.getFieldValue('VALUE');
  var code = name + '.setColorInverse(' + val + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_setEffect = function () {
  var name = this.getFieldValue('XLEDMatrix');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix', name);
  // }
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
  var name = this.getFieldValue('XLEDMatrix');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix', name);
  // }
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
  var name = this.getFieldValue('XLEDMatrix');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix', name);
  // }
  var num = Blockly.Arduino.valueToCode(this, 'NUM',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.showNumber(' + num + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_showNumberPair = function () {
  var name = this.getFieldValue('XLEDMatrix');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix', name);
  // }
  var a = Blockly.Arduino.valueToCode(this, 'A',
    Blockly.Arduino.ORDER_NONE) || 0;
  var b = Blockly.Arduino.valueToCode(this, 'B',
    Blockly.Arduino.ORDER_NONE) || 0;
  var code = name + '.showNumberPair(' + a + ',' + b + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_showString = function () {
  var name = this.getFieldValue('XLEDMatrix');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix', name);
  // }
  var val = Blockly.Arduino.valueToCode(this, 'VALUE',
    Blockly.Arduino.ORDER_NONE) || '';
  var code = name + '.showString(' + val + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_showEmoticon = function () {
  var name = this.getFieldValue('XLEDMatrix');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix', name);
  // }
  var emot = this.getFieldValue('EMOTION');
  var code = name + '.showEmoticon(' + emot + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_showFlag = function () {
  var name = this.getFieldValue('XLEDMatrix');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix', name);
  // }
  var index = this.getFieldValue('INDEX');
  var value = this.getFieldValue('VALUE');
  var code = name + '.showFlag(' + value + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xledmatrix_clear = function () {
  var name = this.getFieldValue('XLEDMatrix');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XLEDMatrix', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XLEDMatrix', name);
  // }
  var code = name + '.clear();\n';
  return code;
};

Blockly.Arduino.xblockly_xvoicebroadcast_reportObject = function () {
  var name = this.getFieldValue('XVoiceBroadcast');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast', name);
  // }
  var index = this.getFieldValue('INDEX');
  var value = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_NONE) || 0;
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportObject(' + index + ',' + value + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xvoicebroadcast_reportTime = function () {
  var name = this.getFieldValue('XVoiceBroadcast');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast', name);
  // }
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
  var name = this.getFieldValue('XVoiceBroadcast');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast', name);
  // }
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
  var name = this.getFieldValue('XVoiceBroadcast');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast', name);
  // }
  var index = this.getFieldValue('INDEX');
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportOperator(' + index + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xvoicebroadcast_reportSound = function () {
  var name = this.getFieldValue('XVoiceBroadcast');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast', name);
  // }
  //var index = this.getFieldValue('INDEX');
  var value = this.getFieldValue('VALUE');
  var repeat = (this.getFieldValue('REPEAT') == 'TRUE') ? 1 : 0;
  // TODO: Assemble Arduino into code variable.
  var code = name + '.reportSound(' + value + ',' + repeat + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xvoicebroadcast_stop = function () {
  var name = this.getFieldValue('XVoiceBroadcast');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast', name);
  // }
  // TODO: Assemble Arduino into code variable.
  var code = name + '.stop();\n';
  return code;
};

Blockly.Arduino.xblockly_xvoicebroadcast_isPlaying = function() {
  var name = this.getFieldValue('XVoiceBroadcast');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XVoiceBroadcast', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XVoiceBroadcast', name);
  // }
  var code = name + '.isPlaying()';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xrgbled_showColor = function () {
  var name = this.getFieldValue('XRGBLed');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XRGBLed', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XRGBLed', name);
  // }
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
  var code = name + '.showColor(' + index + ',' + color + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xrgbled_showRGB = function () {
  var name = this.getFieldValue('XRGBLed');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XRGBLed', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XRGBLed', name);
  // }
  var index = this.getFieldValue('INDEX');
  var r = Blockly.Arduino.valueToCode(this, 'R',
          Blockly.Arduino.ORDER_ATOMIC) || 0;
  var g = Blockly.Arduino.valueToCode(this, 'G',
          Blockly.Arduino.ORDER_ATOMIC) || 0;
  var b = Blockly.Arduino.valueToCode(this, 'B',
          Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = name + '.showColor(' + index + ',' + r + ',' + g + ',' + b + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xrgbled_clear = function () {
  var name = this.getFieldValue('XRGBLed');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XRGBLed', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XRGBLed', name);
  // }
  var index = this.getFieldValue('INDEX');
  var code = name + '.clear(' + index + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xwklightshow_showBreath = function () {
  var name = this.getFieldValue('XRGBLed');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XRGBLed', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XRGBLed', name);
  // }
  var arrObjs = [name];
  var objName = Blockly.Arduino.XBlockly_addService('WKLightShow', 'wk_lgs', arrObjs);
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

Blockly.Arduino.xblockly_xwklightshow_showMeteor = function () {
  var name = this.getFieldValue('XRGBLed');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XRGBLed', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XRGBLed', name);
  // }
  var arrObjs = [name];
  var objName = Blockly.Arduino.XBlockly_addService('WKLightShow', 'wk_lgs', arrObjs);
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

Blockly.Arduino.xblockly_xbuzzer_playTone = function() {
  var name = this.getFieldValue('XBuzzer');
  // if (Blockly.Arduino.XBlockly_isOnBoardModule('XBuzzer', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XBuzzer', name);
  // }
  var frequency = Blockly.Arduino.valueToCode(this, 'FREQUENCY',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var duration = Blockly.Arduino.valueToCode(this, 'DURATION',
      Blockly.Arduino.ORDER_ATOMIC) || 0;
  var code = name + '.playTone(' + frequency + ', ' + duration + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xbuzzer_setNoteParameter = function () {
  var name = this.getFieldValue('XBuzzer');
  // if (Blockly.Arduino.XBlockly_isOnBoardModule('XBuzzer', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XBuzzer', name);
  // }
  var beattime = Blockly.Arduino.valueToCode(this, 'BEATTIME',
    Blockly.Arduino.ORDER_ATOMIC) || 0;
  //0.1秒就是100ms, 2秒就是2000，对应beatTime分别就是10和200, 然后转换为一个字节
  if (beattime < 0.1) {
    beattime = 0.1;
  } else if (beattime > 2.0) {
    beattime = 2.0;
  }
  beattime *= 100;
  var code = name + '.setNoteParameter(' + beattime + ',0);\n';
  return code;
};

Blockly.Arduino.xblockly_xbuzzer_playNote = function () {
  var name = this.getFieldValue('XBuzzer');
  // if (Blockly.Arduino.XBlockly_isOnBoardModule('XBuzzer', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XBuzzer', name);
  // }
  var note = this.getFieldValue('NOTE');
  var scale = this.getFieldValue('SCALE');
  var tone = this.getFieldValue('TONE');
  var beat = this.getFieldValue('BEAT');
  var code = name + '.playNote(' + note + ',' + scale + ',' + tone + ',' + beat + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xwkaudioplayer_playMusic = function () {
  var name = this.getFieldValue('XBuzzer');
  // if (Blockly.Arduino.XBlockly_isOnBoardModule('XBuzzer', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XBuzzer', name);
  // }
  var arrObjs = [name];
  var objName = Blockly.Arduino.XBlockly_addService('WKAudioPlayer', 'wk_adp', arrObjs);
  var val = this.getFieldValue('VALUE');
  //var repeat = (block.getFieldValue('REPEAT') == 'TRUE') ? 1 : 0;
  var code = objName + '.playMusic(' + val/* + ',' + repeat*/ + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xwkaudioplayer_playEffect = function () {
  var name = this.getFieldValue('XBuzzer');
  // if (Blockly.Arduino.XBlockly_isOnBoardModule('XBuzzer', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XBuzzer', name);
  // }
  var arrObjs = [name];
  var objName = Blockly.Arduino.XBlockly_addService('WKAudioPlayer', 'wk_adp', arrObjs);
  var effect = this.getFieldValue('EFFECT');
  var code = objName + '.playSound(' + effect + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xwkaudioplayer_stop = function () {
  var name = this.getFieldValue('XBuzzer');
  // if (Blockly.Arduino.XBlockly_isOnBoardModule('XBuzzer', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XBuzzer', name);
  // }
  var arrObjs = [name];
  var objName = Blockly.Arduino.XBlockly_addService('WKAudioPlayer', 'wk_adp', arrObjs);
  var code = objName + '.stop();\n';
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
  var name = this.getFieldValue('XIRReceiver');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRReceiver', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIRReceiver', name);
  // }
  // var val = Blockly.Arduino.valueToCode(this, 'VALUE',
  //     Blockly.Arduino.ORDER_NONE) || 0;
  var val = this.getFieldValue('PRESSKEY');
  var code = name + '.enableLongPress(' + val + ');\n';
  return code;
};

Blockly.Arduino.xblockly_xirreceiver_available = function() {
  var name = this.getFieldValue('XIRReceiver');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRReceiver', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIRReceiver', name);
  // }
  var code = '(0xFF!=' + name + '.receive())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xirreceiver_receiveNumber = function() {
  var name = this.getFieldValue('XIRReceiver');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRReceiver', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIRReceiver', name);
  // }
  // var val = Blockly.Arduino.valueToCode(this, 'VALUE',
  //     Blockly.Arduino.ORDER_NONE) || 0;
  var val = this.getFieldValue('PRESSKEY');
  var code = '(' + val + '==' + name + '.pick())';
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.xblockly_xirreceiver_waitMessage = function() {
  var name = this.getFieldValue('XIRReceiver');
  // if(Blockly.Arduino.XBlockly_isOnBoardModule('XIRReceiver', name)) {
  //   name = Blockly.Arduino.XBlockly_addOnBoardModule('XIRReceiver', name);
  // }
  var code = name + '.wait();\n';
  return code;
};

/********************************************
System - 系统模块
*********************************************/
