'use strict';

goog.provide('Blockly.Blocks.xblockly');

goog.require('Blockly.Blocks');

// Color
var xblockly_robotColor_construct = '#FDB23B';  //连接
var xblockly_robotColor_actuator = '#5AA4FB'; //运动
var xblockly_robotColor_sensor = '#AD77E6';   //感知
var xblockly_robotColor_display = '#DA71C6';  //展示
var xblockly_robotColor_communicator = '#FD7D70';   //通信
var xblockly_robotColor_system = '#FF6767';   //系统

(function () {
    
    var XBlockly = {};

    XBlockly.MainBoard = '';
    XBlockly.Obj = null;

    XBlockly.getTypeObj = function (type) {
        if (XBlockly.Obj) {
            for (var i = 0; i < XBlockly.Obj.controls.length; i++) {
                var m = XBlockly.Obj.controls[i];
                if (m.type && m.type == type) {
                    return m;
                }
            }
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var m = XBlockly.Obj.modules[i];
                if (m.type && m.type == type) {
                    return m;
                }
            }
        }
        return null;
    }

    XBlockly.getModelObj = function (type, model) {
        if (XBlockly.Obj) {
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var m = XBlockly.Obj.modules[i];
                if (m.type && m.type == type) {
                    for (var j = 0; j < m.models.length; j++) {
                        var o = m.models[j];
                        if (o.id == model) {
                            return o;
                        }
                    }
                }
            }
        }
        return null;
    }

    XBlockly.getPortObj = function (port) {
        return XBlockly.getModelObj('XPORTS', port);
    }

    XBlockly.getTypeObjs = function (defObj) {
        var types = [];
        if (XBlockly.Obj) {
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var m = XBlockly.Obj.modules[i];
                if (m.type != 'XPORTS' && m.type.length > 0 && m.name.length > 0) {
                    types.push(m);
                }
            }
        }
        if (types.length <= 0) {
            if (defObj) {
                types.push(defObj);
            }
        }
        return types;
    }
    
    XBlockly.getTypeObjById = function (id) {
        if (XBlockly.Obj) {
            for (var i = 0; i < XBlockly.Obj.controls.length; i++) {
                var m = XBlockly.Obj.controls[i];
                if (m.objects) {
                    for (var j = 0; j < m.objects.length; j++) {
                        var v = m.objects[j];
                        if (v.id == id) {
                            return m;
                        }
                    }
                }
            }
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var m = XBlockly.Obj.modules[i];
                if (m.objects) {
                    for (var j = 0; j < m.objects.length; j++) {
                        var v = m.objects[j];
                        if (v.id == id) {
                            return m;
                        }
                    }
                }
            }
        }
        return null;
    }

    XBlockly.getModelObjsByType = function (type, defObj) {
        var models = [];
        if (XBlockly.Obj) {
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var m = XBlockly.Obj.modules[i];
                if (m.type && m.type == type) {
                    for (var j = 0; j < m.models.length; j++) {
                        var v = m.models[j];
                        models.push(v);
                    }
                }
            }
        }
        if (models.length <= 0) {
            if (defObj) {
                models.push(defObj);
            }
        }
        return models;
    }

    XBlockly.getObjsByType = function (type, defObj) {
        var objects = [];
        if (XBlockly.Obj) {
            if (type != 'XPORTS') {
                for (var i = 0; i < XBlockly.Obj.controls.length; i++) {
                    var m = XBlockly.Obj.controls[i];
                    if (m.objects && m.type && m.type == type) {
                        for (var j = 0; j < m.objects.length; j++) {
                            var v = m.objects[j];
                            objects.push(v);
                        }
                    }
                }
                for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                    var m = XBlockly.Obj.modules[i];
                    if (m.objects && m.type && m.type == type) {
                        for (var j = 0; j < m.objects.length; j++) {
                            var v = m.objects[j];
                            objects.push(v);
                        }
                    }
                }
            }
        }
        if (objects.length <= 0) {
            if (defObj) {
                objects.push(defObj);
            }
        }
        return objects;
    }

    XBlockly.getObjById = function (id) {
        if (XBlockly.Obj) {
            for (var i = 0; i < XBlockly.Obj.controls.length; i++) {
                var m = XBlockly.Obj.controls[i];
                if (m.objects) {
                    for (var j = 0; j < m.objects.length; j++) {
                        var v = m.objects[j];
                        if (v.id == id) {
                            return v;
                        }
                    }
                }
            }
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var m = XBlockly.Obj.modules[i];
                if (m.objects) {
                    for (var j = 0; j < m.objects.length; j++) {
                        var v = m.objects[j];
                        if (v.id == id) {
                            return v;
                        }
                    }
                }
            }
        }
        return null;
    }

    XBlockly.getObjByTypeId = function (type, id) {
        if (XBlockly.Obj) {
            for (var i = 0; i < XBlockly.Obj.controls.length; i++) {
                var m = XBlockly.Obj.controls[i];
                if (m.objects && m.type && m.type == type) {
                    for (var j = 0; j < m.objects.length; j++) {
                        var v = m.objects[j];
                        if (v.id == id) {
                            return v;
                        }
                    }
                }
            }
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var m = XBlockly.Obj.modules[i];
                if (m.objects && m.type && m.type == type) {
                    for (var j = 0; j < m.objects.length; j++) {
                        var v = m.objects[j];
                        if (v.id == id) {
                            return v;
                        }
                    }
                }
            }
        }
        return null;
    }

    XBlockly.addOrUpdateObj = function (type, name, id) {
        if (type && type.length > 0 && name && name.length > 0 && id && id.length > 0) {
            if (XBlockly.Obj) {
                for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                    var m = XBlockly.Obj.modules[i];
                    if (m.objects && m.type && m.type == type) {
                        for(var j = 0; j < m.objects.length; j++) {
                            if(m.objects[j].id == id) {
                                m.objects[j].name = name;
                                return;
                            }
                        }
                        m.objects.push({ name: name, id: id });
                        return;
                    }
                }
            }
        }
    }

    XBlockly.resetAllObjs = function () {
        if (XBlockly.Obj) {
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var m = XBlockly.Obj.modules[i];
                if (m.type != 'XPORTS' && m.objects) {
                    for (var j = m.objects.length - 1; j >= 0; j--) {
                        m.objects.splice(j, 1);
                    }
                }
            }
        }
    }

    XBlockly.getOnBoardObjsByType = function (type, defObj) {
        var objects = [];
        if (XBlockly.Obj) {
            if (type != 'XPORTS') {
                for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                    var m = XBlockly.Obj.modules[i];
                    if (m.onboards && m.type && m.type == type) {
                        for (var j = 0; j < m.onboards.length; j++) {
                            var v = m.onboards[j];
                            objects.push(v);
                        }
                    }
                }
            }
        }
        if (objects.length <= 0) {
            if (defObj) {
                objects.push(defObj);
            }
        }
        return objects;
    }

    XBlockly.isPortConnectable = function (portObj, modelObj) {
        if (portObj && modelObj) {
            if (portObj.scope.indexOf(modelObj.scope) >= 0) {
                return true;
            } else {
                var arrScope = modelObj.scope.split(' ');
                for(var i = 0; i < arrScope.length; i++) {
                    if (portObj.scope.indexOf(arrScope[i]) >= 0) {
                        return true;
                    } 
                }
            }
        }
        return false;
    }

    XBlockly.getConnectablePortObjs = function (defObj) {
        var objects = [];
        if (XBlockly.Obj) {
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var m = XBlockly.Obj.modules[i];
                if (m.models && m.type && m.type == 'XPORTS') {
                    for (var j = 0; j < m.models.length; j++) {
                        var o = m.models[j];
                        if (!XBlockly.isPortConnected(o.id)) {
                            objects.push(o);
                        }
                    }
                }
            }
        }
        if (objects.length <= 0) {
            if (defObj) {
                objects.push(defObj);
            }
        }
        return objects;
    }

    XBlockly.getConnectableTypeObjsByPort = function (port, defObj) {
        var types = [];
        if (XBlockly.Obj) {
            var portObj = XBlockly.getPortObj(port);
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var m = XBlockly.Obj.modules[i];
                if (m.type && m.type != 'XPORTS') {
                    for (var j = 0; j < m.models.length; j++) {
                        var o = m.models[j];
                        if (XBlockly.isPortConnectable(portObj, o)) {
                            types.push(m); //只要找到一个型号匹配的就跳出循环，不然会重复增加该type
                            break;
                        }
                    }
                }
            }
        }
        if (types.length <= 0) {
            if (defObj) {
                types.push(defObj);
            }
        }
        return types;
    }

    XBlockly.getConnectableModelObjsByPort = function (port, type, defObj) {
        var models = [];
        if (XBlockly.Obj) {
            var portObj = XBlockly.getPortObj(port);
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var m = XBlockly.Obj.modules[i];
                if (m.type && m.type == type) {
                    for (var j = 0; j < m.models.length; j++) {
                        var o = m.models[j];
                        if (XBlockly.isPortConnectable(portObj, o)) {
                            models.push(o);
                        }
                    }
                    break;
                }
            }
        }
        if (models.length <= 0) {
            if (defObj) {
                models.push(defObj);
            }
        }
        return models;
    }

    XBlockly.removeConnectToPortObj = function (port) {
        if (XBlockly.Obj) {
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var remove = false;
                var m = XBlockly.Obj.modules[i];
                if (m.objects && m.type && m.type != 'XPORTS') {
                    for (var j = 0; j < m.objects.length; j++) {
                        var v = m.objects[j];
                        if (v.id == port) {
                            m.objects.splice(j, 1);
                            remove = true;
                            break;
                        }
                    }
                }
                if (remove) {
                    break;
                }
            }
        }
    }

    XBlockly.resetConnectToPortObjs = function () {
        var xportsObj = XBlockly.getTypeObj('XPORTS');
        if (xportsObj) {
            for (var i = 0; i < xportsObj.models.length; i++) {
                var m = xportsObj.models[i];
                XBlockly.removeConnectToPortObj(m.id);
            }
        }
    }

    //记录端口使用的MAP
    XBlockly.Port2BlockId = new Map();
    XBlockly.BlockId2Port = new Map();

    XBlockly.resetPort = function () {
        XBlockly.resetConnectToPortObjs();
        XBlockly.Port2BlockId = new Map();
        XBlockly.BlockId2Port = new Map();
    }

    XBlockly.isPortConnected = function (port) {
        return XBlockly.Port2BlockId.has(port);
    }

    XBlockly.isPortConnectedWithType = function (port, type) {
        if (XBlockly.Obj) {
            var find = false;
            for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                var m = XBlockly.Obj.modules[i];
                if (m.objects && m.type && m.type == type) {
                    for (var j = 0; j < m.objects.length; j++) {
                        var v = m.objects[j];
                        if (v.id == port) {
                            find = true;
                            break;
                        }
                    }
                }
                if (find) {
                    break;
                }
            }
            return find;
        }
        return false;
    }

    XBlockly.isPortConnectedWithBlockId = function (port, blockId) {
        if (XBlockly.Port2BlockId.has(port)) {
            return blockId == XBlockly.Port2BlockId.get(port);
        }
        return false;
    }

    XBlockly.addPort = function (type, portObj, blockId) {
        if (type && type.length > 0 && portObj && blockId && blockId.length > 0) {
            XBlockly.Port2BlockId.set(portObj.id, blockId);
            XBlockly.BlockId2Port.set(blockId, portObj.id);
            if (XBlockly.Obj) {
                for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                    var m = XBlockly.Obj.modules[i];
                    if (m.objects && m.type && m.type == type) {
                        m.objects.push({ name: portObj.name, id: portObj.id });
                        return;
                    }
                }
            }
        }
    }

    XBlockly.removePortByBlockId = function (blockId) {
        if (XBlockly.BlockId2Port.has(blockId)) {
            var port = XBlockly.BlockId2Port.get(blockId);
            if (XBlockly.Obj) {
                var remove = false;
                for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
                    var m = XBlockly.Obj.modules[i];
                    if (m.objects && m.type && m.type != 'XPORTS') {
                        for (var j = 0; j < m.objects.length; j++) {
                            var v = m.objects[j];
                            if (v.id == port) {
                                m.objects.splice(j, 1);
                                remove = true;
                                break;
                            }
                        }
                    }
                    if (remove) {
                        break;
                    }
                }
            }
            XBlockly.Port2BlockId.delete(port);
            XBlockly.BlockId2Port.delete(blockId);
        }
    }

    XBlockly.removePort = function (type, port, blockId) {
        XBlockly.removePortByBlockId(blockId);
        if (XBlockly.Port2BlockId.has(port)) {
            XBlockly.removePortByBlockId(XBlockly.Port2BlockId.get(port));
        }
    }

    //记录创建的图块
    XBlockly.Block2BlockId = new Map();
    XBlockly.BlockId2Block = new Map();

    XBlockly.resetBlock = function () {
        XBlockly.Block2BlockId = new Map();
        XBlockly.BlockId2Block = new Map();
    }

    XBlockly.addBlock = function (blockObj, blockId) {
        XBlockly.Block2BlockId.set(blockObj, blockId);
        XBlockly.BlockId2Block.set(blockId, blockObj);
    }

    XBlockly.removeBlockByBlockId = function (blockId) {
        if (XBlockly.BlockId2Block.has(blockId)) {
            var blockObj = XBlockly.BlockId2Block.get(blockId);
            XBlockly.Block2BlockId.delete(blockObj);
            XBlockly.BlockId2Block.delete(blockId);
        }
    }

    XBlockly.hasAnyBlockByType = function (type, port) {
        var ltype = type.toLowerCase();
        for (var kv of XBlockly.Block2BlockId) {
            var blockObj = kv[0];
            if (blockObj.type.indexOf(ltype) == 0) {
                if (port) {
                    if (port == blockObj.getFieldValue(type)) {
                        return true;
                    } else {
                        return false;
                    }
                }
                return true;
            }
        }
        return false;
    }

    XBlockly.resetHideCode = function () {
        //具体应用实现不一样的代码生成
    }

    XBlockly.genHideCode = function () {
        //具体应用实现不一样的代码生成
    }

    XBlockly.onBlockCreate = function (e) {
        e.ids.forEach(id => {
            var blockObj = XBlockly.workspace.getBlockById(id);
            if (blockObj) {
                XBlockly.addBlock(blockObj, id);
            }
        });
    }

    XBlockly.onBlockDelete = function (e) {
        e.ids.forEach(id => {
            XBlockly.removePortByBlockId(id);
            XBlockly.removeBlockByBlockId(id);
        });
    }

    XBlockly.onBlockChange = function (e) {
        if (e.type === 'create') {
            //alert(e);
            XBlockly.onBlockCreate(e);
        }
        else if (e.type === 'delete') {
            //alert(e);
            XBlockly.onBlockDelete(e);
        }
    }
    
    XBlockly.onBlockReset = function () {
        XBlockly.resetPort();
        XBlockly.resetBlock();
    }

    XBlockly.genScope = function (type, func) {
        var scope = '';
        var subfuncs = [];
        if (type == 'XRJ45') {
            //用三个字符标识一个功能，比如` func：CDR,XXX`,用逗号分隔，标识支持` CDR`或者` XXX`的端口连接
            subfuncs = func.split(',');
        } else {
            //func是端口的功能描述，` ####`四个字符表示，这里用` #`表示空，比如` #2PP`，其中用数字表示数字端口，数字是向下兼容的，
            //` #2PP`这里的2就支持2和1的端口连接，非数字标识的字母向下支持是支持子串，这里的` PP`就支持` PP`和` P`端口连接
            for (var i = 0; i < 4; i++) {
                if (func[i] == ' ' || func[i] == '#') {
                    //
                } else if (func[i] >= '1' && func[i] <= '9') {
                    for (var j = '1'; j <= func[i]; j++) {
                        subfuncs.push(j);
                    }
                } else {
                    var substr = func[i];
                    for (i++; i < 4;) {
                        if (substr[substr.length - 1] == func[i]) {
                            substr += func[i];
                            i++;
                        } else {
                            i--;
                            break;
                        }
                    }
                    for (var j = 0; j < substr.length; j++) {
                        subfuncs.push(substr.substr(0, j + 1));
                    }
                }
            }
        }
        if(subfuncs.length<=0) {
            scope += type;
        } else {
            for (var i = 0; i < subfuncs.length; i++) {
                if (i < (subfuncs.length - 1)) {
                    scope += type + subfuncs[i] + ' ';
                } else {
                    scope += type + subfuncs[i];
                }
            }
        }
        return scope;
    }
    
    XBlockly.init = function (obj) {
      //XBlockly.resetHideCode();
      XBlockly.resetPort();
      XBlockly.resetBlock();
      XBlockly.Obj = obj;
      if (XBlockly.Obj) {
          if (!XBlockly.Obj.selectedObj) {
              XBlockly.Obj.selectedObj = null;
          }
          if (!XBlockly.Obj.controls) {
              XBlockly.Obj.controls = [];
          }
          for (var i = 0; i < XBlockly.Obj.modules.length; i++) {
              var m = XBlockly.Obj.modules[i];
              for (var j = 0; j < m.models.length; j++) {
                  var o = m.models[j];
                  o.scope = XBlockly.genScope(o.type, o.func);
              }
          }
          if (!XBlockly.Obj.services) {
              XBlockly.Obj.services = [
              ];
          }
      }
  }

  window.XBlockly = XBlockly;
    
  var jsonObjects = '{"modules":[{"type":"XDualDCMotor","name":"双直流电机","models":[{"func":"####","type":"XRJ25","id":"DDM3300"}],"objects":[],"onboards":[{"id":"DDM","model":"DDM3001","name":"板载-DDM"}]},{"type":"XBuzzer","name":"蜂鸣器","models":[{"func":"D###","type":"XRJ25","id":"BUZ3300"}],"objects":[],"onboards":[{"id":"BUZ","model":"BUZ4000","name":"板载-BUZ"}]},{"type":"XButton","name":"按钮","models":[{"func":"A###","type":"XRJ25","id":"BTN3300"}],"objects":[]},{"type":"XLightSensor","name":"光线传感器","models":[{"func":"A###","type":"XRJ25","id":"LIG3300"}],"objects":[],"onboards":[{"id":"LIG","model":"LIG4000","name":"板载-LIG"}]},{"type":"XSoundSensor","name":"声音传感器","models":[{"func":"A###","type":"XRJ25","id":"SND3300"}],"objects":[],"onboards":[{"id":"SND","model":"SND3000","name":"板载-SND"}]},{"type":"XIRReceiver","name":"红外接收器","models":[{"func":"H###","type":"XRJ25","id":"IRR3300"}],"objects":[],"onboards":[{"id":"IRR","model":"IRR3000","name":"板载-IRR"}]},{"type":"XIRTracking","name":"红外循迹传感器","models":[{"func":"H###","type":"XRJ25","id":"IRT3320"}],"objects":[]},{"type":"XIRTracking6","name":"六路红外循迹传感器","models":[{"func":"####","type":"XRJ25","id":"IRT3360"}],"objects":[]},{"type":"XUltrasonic","name":"超声波传感器","models":[{"func":"H###","type":"XRJ25","id":"ULS3600"}],"objects":[]},{"type":"XSegDisplay","name":"数码管","models":[{"func":"H###","type":"XRJ25","id":"SGD4300"}],"objects":[]},{"type":"XLEDMatrix","name":"LED面板","models":[{"func":"####","type":"XRJ25","id":"LMT3300"}],"objects":[]},{"type":"XVoiceBroadcast","name":"语音播报器","models":[{"func":"####","type":"XRJ25","id":"VBC3300"}],"objects":[]},{"type":"XIRAvoiding","name":"红外避障传感器","models":[{"func":"H###","type":"XRJ25","id":"IRA3300"}],"objects":[]},{"type":"XPotentiometer","name":"电位器","models":[{"func":"A###","type":"XRJ25","id":"PTM3300"}],"objects":[]},{"type":"XRGBLed","name":"RGB彩灯","models":[{"func":"D###","type":"XRJ25","id":"RGB3340"}],"objects":[],"onboards":[{"id":"RGB","model":"RGB3060","name":"板载-RGB"}]},{"type":"XHumiture","name":"温湿度传感器","models":[{"func":"D###","type":"XRJ25","id":"HUM3300"}],"objects":[]},{"type":"XPIR","name":"人体红外传感器","models":[{"func":"D###","type":"XRJ25","id":"PIR3300"}],"objects":[]},{"type":"XShockSensor","name":"震动传感器","models":[{"func":"D###","type":"XRJ25","id":"SKS3300"}],"objects":[]},{"type":"XBluetooth","name":"蓝牙","models":[{"func":"U###","type":"XIP45","id":"BLT4140"}],"objects":[]},{"type":"XServo","name":"舵机","models":[],"objects":[],"onboards":[{"id":"SVO","model":"SVO3000","name":"板载-SVO"},{"id":"SVO1","model":"SVO3000","name":"板载-SVO1"},{"id":"SVO2","model":"SVO3000","name":"板载-SVO2"}]},{"name":"端口","type":"XPORTS","models":[{"name":"端口1","id":"1","type":"XRJ25","func":"DHP#"},{"name":"端口2","id":"2","type":"XRJ25","func":"DHAK"},{"name":"端口3","id":"3","type":"XRJ25","func":"DHP#"},{"name":"端口4","id":"4","type":"XRJ25","func":"DHP#"},{"name":"端口5","id":"5","type":"XRJ25","func":"DHPR"},{"name":"端口6","id":"6","type":"XRJ25","func":"DHA#"},{"name":"端口7","id":"7","type":"XRJ25","func":"DHA#"},{"name":"端口8","id":"8","type":"XRJ25","func":"DHP#"},{"name":"端口9","id":"9","type":"XIP45","func":"U###"}]}]}';
  window.XBlockly.init(JSON.parse(jsonObjects));
})();

Blockly.getXBlocklyNameTypes = function (defVar) {
    var myVars = [];
    var myTypes = window.XBlockly.getTypeObjs();
    if (myTypes) {
        for (var i = 0; i < myTypes.length; i++) {
            var o = myTypes[i];
            if(o.models && o.models.length > 0) {
              myVars.push([o.name, o.type]);
            }
        }
    }
    if (myVars.length <= 0) {
        if (defVar) {
            myVars.push(defVar);
        }
    }
    return myVars;
}

Blockly.getXBlocklyOnBoardNameTypes = function (defVar) {
    var myVars = [];
    var myTypes = window.XBlockly.getTypeObjs();
    if (myTypes) {
        for (var i = 0; i < myTypes.length; i++) {
            var o = myTypes[i];
            if(o.onboards && o.onboards.length > 0) {
                myVars.push([o.name, o.type]);
            }
        }
    }
    if (myVars.length <= 0) {
        if (defVar) {
            myVars.push(defVar);
        }
    }
    return myVars;
}

Blockly.getXBlocklyNameModelsByType = function (type, defVar) {
    var myVars = [];
    if (type) {
        var myModels = window.XBlockly.getModelObjsByType(type);
        if (myModels) {
            for (var i = 0; i < myModels.length; i++) {
                var o = myModels[i];
                myVars.push([o.id, o.id]);
            }
        }
    }
    if (myVars.length <= 0) {
        if (defVar) {
            myVars.push(defVar);
        }
    }
    return myVars;
}

Blockly.getXBlocklyOnBoardNameLabelsByType = function (type, defVar) {
  var myVars = [];
  if (type) {
      var myOnBoardObjs = window.XBlockly.getOnBoardObjsByType(type);
      if (myOnBoardObjs) {
          for (var i = 0; i < myOnBoardObjs.length; i++) {
              var o = myOnBoardObjs[i];
              myVars.push([o.id, o.id]);
          }
      }
  }
  if (myVars.length <= 0) {
      if (defVar) {
          myVars.push(defVar);
      }
  }
  return myVars;
}

Blockly.getXBlocklyNameObjsByType = function (type, defVar) {
    var myVars = [];
    if (type) {
        var myObjects = window.XBlockly.getObjsByType(type);
        if (myObjects) {
            for (var i = 0; i < myObjects.length; i++) {
                var o = myObjects[i];
                myVars.push([o.name, o.id]);
            }
        }
    }
    if (myVars.length <= 0) {
        if (defVar) {
            myVars.push(defVar);
        }
    }
    return myVars;
}

Blockly.getXBlocklyNamePorts = function (defVar) {
    var myVars = [];
    var myPorts = window.XBlockly.getConnectablePortObjs();
    if (myPorts) {
        for (var i = 0; i < myPorts.length; i++) {
            var o = myPorts[i];
            myVars.push([o.id, o.id]);
        }
    }
    if (myVars.length <= 0) {
        if (defVar) {
            myVars.push(defVar);
        }
    }
    return myVars;
}

Blockly.getXBlocklyConnectableNameTypesByPort = function (port, defVar) {
    var myVars = [];
    var myTypes = window.XBlockly.getConnectableTypeObjsByPort(port);
    if (myTypes) {
        for (var i = 0; i < myTypes.length; i++) {
            var o = myTypes[i];
            myVars.push([o.name, o.type]);
        }
    }
    if (myVars.length <= 0) {
        if (defVar) {
            myVars.push(defVar);
        }
    }
    return myVars;
}

Blockly.getXBlocklyConnectableNameModelsByPort = function (port, type, defVar) {
    var myVars = [];
    if (type) {
        var myModels = window.XBlockly.getConnectableModelObjsByPort(port, type);
        if (myModels) {
            for (var i = 0; i < myModels.length; i++) {
                var o = myModels[i];
                myVars.push([o.id, o.id]);
            }
        }
    }
    if (myVars.length <= 0) {
        if (defVar) {
            myVars.push(defVar);
        }
    }
    return myVars;
}

Blockly.updateXBlocklyPort = function (type, port, blockId) {
    /*if(!window.XBlockly.isPortConnectedWithBlockId(port,blockId) || !window.XBlockly.isPortConnectedWithType(port,type)) {
        window.XBlockly.removePort(type, port, blockId);
        var portObj = window.XBlockly.getPortObj(port);
        if (portObj) {
            window.XBlockly.addPort(type, portObj, blockId);
            return true;
        }
    }*/
    return false;
}

Blockly.getXBlocklyModelObj = function (port) {
    var typeObj = window.XBlockly.getTypeObjById(port);
    if(typeObj) {
        return window.XBlockly.getModelObj(typeObj.type, typeObj.model);
    }
    return null;
}

Blockly.getXBlocklyVarName = function (type, port) {
    var name = "";
    var typeObj = window.XBlockly.getTypeObj(type);
    if (typeObj) {
        if (typeObj.type == 'XIODriver') {
            name = ('io_' + port).toLowerCase();
        } else {
            // if (window.XBlockly.isOnBoardModule(typeObj.type, port)) {
            //     name = (port).toLowerCase();
            // } else {
                if (typeObj.models && typeObj.models.length > 0) {
                    name = (typeObj.models[0].id.substring(0, 3) + '_p' + port).toLowerCase();
                } else {
                    name = (port).toLowerCase();
                }
            // }
        }
    }
    return name;
}

Blockly.getXBlocklyVarNameByLabel = function (type, label) {
    var name = "";
    var typeObj = window.XBlockly.getTypeObj(type);
    if (typeObj) {
        if (typeObj.type == 'XIODriver') {
            name = ('io_' + label).toLowerCase();
        } else {
            name = (label + '_onboard').toLowerCase();
        }
    }
    return name;
}

Blockly.getXBlocklyVarPin = function (pin) {
  var varPin = pin;
  var intPin = parseInt(pin);
  if(intPin >= 14) {
    varPin = 'A' + (intPin - 14).toString();
  }
  return varPin;
}

Blockly.getXBlocklyVarNameByPin = function (type, pin1, pin2, pin3, pin4) {
  var name = "";
  var typeObj = window.XBlockly.getTypeObj(type);
  if (typeObj) {
      if (typeObj.type == 'XIODriver') {
          name = 'io_' + pin1 + (pin2 ? '_' + pin2 : '') + (pin3 ? '_' + pin3 : '') + (pin4 ? '_' + pin4 : '');
      } else {
          if (typeObj.models && typeObj.models.length > 0) {
              name = typeObj.models[0].id.substring(0, 3).toLowerCase();
          } else {
              name = (type).toLowerCase();
          }
          name += ('_' + pin1 + (pin2 ? '_' + pin2 : '') + (pin3 ? '_' + pin3 : '') + (pin4 ? '_' + pin4 : ''));
      }
  }
  return name;
}

/********************************************
Construct - 连接模块
*********************************************/

Blockly.Blocks.xblockly_construct_INIT = {
  init: function () {
    var dropdownInstances = new Blockly.FieldDropdown([
      ['Arduino/Genuino Uno', 'Arduino/Genuino Uno']
      ,['Arduino/WuKong', 'Arduino/WuKong']
      ,['Arduino/PanGu', 'Arduino/PanGu']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIODriver.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XMAINBOARD_1)
      .appendField(dropdownInstances, "XMainBoard")
      .appendField(Blockly.Msg.MY_XMAINBOARD_2);
    this.setInputsInline(true);
    //this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, Boolean);
    this.setColour(xblockly_robotColor_construct);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

function construct_onchange() {
  if (!this.workspace) return;  // Block has been deleted.

  if(this.isInFlyout) return;

  if(this.isInMutator) return;

  if(this.blockType) {
    var type = this.blockType;
    if(type=='XPORTS') {
      type = this.getFieldValue('TYPE');
      //var modelField = this.getField('MODEL');
      //modelField.init.apply(this,[]);
    }
    var model = this.getFieldValue('MODEL');
    var port = this.getFieldValue('PORT');
    Blockly.updateXBlocklyPort(type,port,this.id);
  }
};

Blockly.Blocks.xblockly_construct_XPORTS = {
  init: function () {
    var _this = this;
    this.blockType = 'XPORTS';
    var textInputVar = this.textInputVar = new Blockly.FieldTextInput('');
    function getMyTypes() {
      return Blockly.getXBlocklyNameTypes([Blockly.Msg.MY_NULL, '']);
    }
    var dropdownTypes = this.dropdownTypes = new Blockly.FieldDropdown(getMyTypes);
    function getMyModels() {
      return Blockly.getXBlocklyNameModelsByType(dropdownTypes.value_, [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownModels = this.dropdownModels = new Blockly.FieldDropdown(getMyModels);
    function getMyPorts() {
      return Blockly.getXBlocklyNamePorts([Blockly.Msg.MY_NULL, '']);
    }
    var dropdownPorts = this.dropdownPorts = new Blockly.FieldDropdown(getMyPorts);
    textInputVar.setValue(Blockly.getXBlocklyVarName(getMyTypes()[0][1], getMyPorts()[0][1]));
    dropdownTypes.onItemSelected = function (menu, menuItem) {
        var value = menuItem.getValue();
        if (this.sourceBlock_) {
            value = this.callValidator(value);

            var models = Blockly.getXBlocklyNameModelsByType(value, [Blockly.Msg.MY_NULL, '']);
            _this.textInputVar.setValue(Blockly.getXBlocklyVarName(value, dropdownPorts.value_));
            _this.dropdownModels.setValue(models[0][1]);
        }
        if (value !== null) {
            this.setValue(value);
        }
    };
    dropdownPorts.onItemSelected = function (menu, menuItem) {
        var value = menuItem.getValue();
        if (this.sourceBlock_) {
            value = this.callValidator(value);

            _this.textInputVar.setValue(Blockly.getXBlocklyVarName(dropdownTypes.value_, value));
        }
        if (value !== null) {
            this.setValue(value);
        }
    };
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIODriver.png", 16, 16, "*"))
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_TYPE_1)
        .appendField(dropdownTypes, "TYPE")
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_TYPE_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_MODEL_1)
        .appendField(dropdownModels, "MODEL")
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_MODEL_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_VAR_1)
        .appendField(textInputVar, 'VAR')
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_VAR_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_CONNECT);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_1)
        .appendField(dropdownPorts, "PORT")
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'String');
    this.setColour(xblockly_robotColor_construct);
  },

  onchange: function() {
    construct_onchange.apply(this,[]);
  }
};

Blockly.Blocks.xblockly_construct_ONBOARD = {
  init: function () {
    var _this = this;
    var textInputVar = this.textInputVar = new Blockly.FieldTextInput('');
    function getMyTypes() {
      return Blockly.getXBlocklyOnBoardNameTypes([Blockly.Msg.MY_NULL, '']);
    }
    var dropdownTypes = this.dropdownTypes = new Blockly.FieldDropdown(getMyTypes);
    function getMyLabels() {
      return Blockly.getXBlocklyOnBoardNameLabelsByType(dropdownTypes.value_, [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownLabels = this.dropdownLabels = new Blockly.FieldDropdown(getMyLabels);
    textInputVar.setValue(Blockly.getXBlocklyVarNameByLabel(getMyTypes()[0][1], getMyLabels()[0][1]));
    dropdownTypes.onItemSelected = function (menu, menuItem) {
        var value = menuItem.getValue();
        if (this.sourceBlock_) {
            value = this.callValidator(value);

            var labels = Blockly.getXBlocklyOnBoardNameLabelsByType(value, [Blockly.Msg.MY_NULL, '']);
            _this.textInputVar.setValue(Blockly.getXBlocklyVarNameByLabel(value, dropdownLabels.value_));
            _this.dropdownLabels.setValue(labels[0][1]);
        }
        if (value !== null) {
            this.setValue(value);
        }
    };
    dropdownLabels.onItemSelected = function (menu, menuItem) {
        var value = menuItem.getValue();
        if (this.sourceBlock_) {
            value = this.callValidator(value);

            _this.textInputVar.setValue(Blockly.getXBlocklyVarNameByLabel(dropdownTypes.value_, value));
        }
        if (value !== null) {
            this.setValue(value);
        }
    };
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIODriver.png", 16, 16, "*"))
        .appendField(Blockly.Msg.MY_CONSTRUCT_ONBOARD);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_TYPE_1)
        .appendField(dropdownTypes, "TYPE")
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_TYPE_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_LABEL_1)
        .appendField(dropdownLabels, "LABEL")
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_LABEL_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_VAR_1)
        .appendField(textInputVar, 'VAR');
        //.appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_VAR_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'String');
    this.setColour(xblockly_robotColor_construct);
  },

  onchange: function() {
    construct_onchange.apply(this,[]);
  }
};

Blockly.Blocks.xblockly_xbutton_INIT = {
  init: function () {
    var _this = this;
    var textInputVar = this.textInputVar = new Blockly.FieldTextInput('');
    function getMyModels() {
      return Blockly.getXBlocklyNameModelsByType('XButton', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownModels = this.dropdownModels = new Blockly.FieldDropdown(getMyModels);
    var dropdownPins = this.dropdownPins = new Blockly.FieldDropdown([
      // ['0', '0']
      // , ['1', '1']
      // , ['2', '2']
      // , ['3', '3']
      // , ['4', '4']
      // , ['5', '5']
      // , ['6', '6']
      // , ['7', '7']
      // , ['8', '8']
      // , ['9', '9']
      // , ['10', '10']
      // , ['11', '11']
      // , ['12', '12']
      // , ['13', '13']
      ['A0', '14']
      , ['A1', '15']
      , ['A2', '16']
      , ['A3', '17']
      , ['A4', '18']
      , ['A5', '19']
      , ['A6', '20']
      , ['A7', '21']
    ]);
    textInputVar.setValue(Blockly.getXBlocklyVarNameByPin('XButton', '0'));
    dropdownPins.onItemSelected = function (menu, menuItem) {
        var value = menuItem.getValue();
        if (this.sourceBlock_) {
            value = this.callValidator(value);

            _this.textInputVar.setValue(Blockly.getXBlocklyVarNameByPin('XButton', Blockly.getXBlocklyVarPin(value)));
        }
        if (value !== null) {
            this.setValue(value);
        }
    };
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XButton.png", 16, 16, "*"))
        .appendField(Blockly.Msg.MY_CONSTRUCT_XBUTTON);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_MODEL_1)
        .appendField(dropdownModels, "MODEL")
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_MODEL_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_VAR_1)
        .appendField(textInputVar, 'VAR')
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_VAR_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_PIN_CONNECT);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_PIN_AO)
        .appendField(dropdownPins, "PIN")
        .appendField('');
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'String');
    this.setColour(xblockly_robotColor_construct);
  }
};

Blockly.Blocks.xblockly_xbuzzer_INIT = {
  init: function () {
    var _this = this;
    var textInputVar = this.textInputVar = new Blockly.FieldTextInput('');
    function getMyModels() {
      return Blockly.getXBlocklyNameModelsByType('XBuzzer', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownModels = this.dropdownModels = new Blockly.FieldDropdown(getMyModels);
    var dropdownPins = this.dropdownPins = new Blockly.FieldDropdown([
      ['0', '0']
      , ['1', '1']
      , ['2', '2']
      , ['3', '3']
      , ['4', '4']
      , ['5', '5']
      , ['6', '6']
      , ['7', '7']
      , ['8', '8']
      , ['9', '9']
      , ['10', '10']
      , ['11', '11']
      , ['12', '12']
      , ['13', '13']
      , ['A0', '14']
      , ['A1', '15']
      , ['A2', '16']
      , ['A3', '17']
      , ['A4', '18']
      , ['A5', '19']
      //, ['A6', '20']
      //, ['A7', '21']
    ]);
    textInputVar.setValue(Blockly.getXBlocklyVarNameByPin('XBuzzer', '0'));
    dropdownPins.onItemSelected = function (menu, menuItem) {
        var value = menuItem.getValue();
        if (this.sourceBlock_) {
            value = this.callValidator(value);
            
            _this.textInputVar.setValue(Blockly.getXBlocklyVarNameByPin('XBuzzer', Blockly.getXBlocklyVarPin(value)));
        }
        if (value !== null) {
            this.setValue(value);
        }
    };
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XBuzzer.png", 16, 16, "*"))
        .appendField(Blockly.Msg.MY_CONSTRUCT_XBUZZER);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_MODEL_1)
        .appendField(dropdownModels, "MODEL")
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_MODEL_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_VAR_1)
        .appendField(textInputVar, 'VAR')
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_VAR_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_PIN_CONNECT);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_PIN_DI)
        .appendField(dropdownPins, "PIN")
        .appendField('');
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'String');
    this.setColour(xblockly_robotColor_construct);
  }
};

Blockly.Blocks.xblockly_xdualdcmotor_INIT = {
  init: function () {
    var _this = this;
    var textInputVar = this.textInputVar = new Blockly.FieldTextInput('');
    function getMyModels() {
      return Blockly.getXBlocklyNameModelsByType('XDualDCMotor', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownModels = this.dropdownModels = new Blockly.FieldDropdown(getMyModels);
    var dropdownSDAs = this.dropdownSDAs = new Blockly.FieldDropdown([
      // ['0', '0']
      // , ['1', '1']
      // , ['2', '2']
      // , ['3', '3']
      // , ['4', '4']
      // , ['5', '5']
      // , ['6', '6']
      // , ['7', '7']
      // , ['8', '8']
      // , ['9', '9']
      // , ['10', '10']
      // , ['11', '11']
      // , ['12', '12']
      // , ['13', '13']
      // , ['A0', '14']
      // , ['A1', '15']
      // , ['A2', '16']
      // , ['A3', '17']
      ['A4', '18']
      // , ['A5', '19']
      // , ['A6', '20']
      // , ['A7', '21']
    ]);
    var dropdownSCLs = this.dropdownSCLs = new Blockly.FieldDropdown([
      // ['0', '0']
      // , ['1', '1']
      // , ['2', '2']
      // , ['3', '3']
      // , ['4', '4']
      // , ['5', '5']
      // , ['6', '6']
      // , ['7', '7']
      // , ['8', '8']
      // , ['9', '9']
      // , ['10', '10']
      // , ['11', '11']
      // , ['12', '12']
      // , ['13', '13']
      // , ['A0', '14']
      // , ['A1', '15']
      // , ['A2', '16']
      // , ['A3', '17']
      // , ['A4', '18']
      ['A5', '19']
      // , ['A6', '20']
      // , ['A7', '21']
    ]);
    var dropdownRSTs = this.dropdownRSTs = new Blockly.FieldDropdown([
      ['0', '0']
      , ['1', '1']
      , ['2', '2']
      , ['3', '3']
      , ['4', '4']
      , ['5', '5']
      , ['6', '6']
      , ['7', '7']
      , ['8', '8']
      , ['9', '9']
      , ['10', '10']
      , ['11', '11']
      , ['12', '12']
      , ['13', '13']
      , ['A0', '14']
      , ['A1', '15']
      , ['A2', '16']
      , ['A3', '17']
      // , ['A4', '18']
      // , ['A5', '19']
      // , ['A6', '20']
      // , ['A7', '21']
    ]);
    var dropdownSELs = this.dropdownSELs = new Blockly.FieldDropdown([
      ['0', '0']
      , ['1', '1']
      , ['2', '2']
      , ['3', '3']
      , ['4', '4']
      , ['5', '5']
      , ['6', '6']
      , ['7', '7']
      , ['8', '8']
      , ['9', '9']
      , ['10', '10']
      , ['11', '11']
      , ['12', '12']
      , ['13', '13']
      , ['A0', '14']
      , ['A1', '15']
      , ['A2', '16']
      , ['A3', '17']
      // , ['A4', '18']
      // , ['A5', '19']
      // , ['A6', '20']
      // , ['A7', '21']
    ]);
    textInputVar.setValue(Blockly.getXBlocklyVarNameByPin('XDualDCMotor', 'A4', 'A5', '0', '0'));
    dropdownSDAs.onItemSelected = function (menu, menuItem) {
        var value = menuItem.getValue();
        if (this.sourceBlock_) {
            value = this.callValidator(value);
            
            _this.textInputVar.setValue(Blockly.getXBlocklyVarNameByPin('XDualDCMotor'
            , Blockly.getXBlocklyVarPin(value), Blockly.getXBlocklyVarPin(dropdownSCLs.value_)
            , Blockly.getXBlocklyVarPin(dropdownRSTs.value_), Blockly.getXBlocklyVarPin(dropdownSELs.value_)));
        }
        if (value !== null) {
            this.setValue(value);
        }
    };
    dropdownSCLs.onItemSelected = function (menu, menuItem) {
        var value = menuItem.getValue();
        if (this.sourceBlock_) {
            value = this.callValidator(value);
            
            _this.textInputVar.setValue(Blockly.getXBlocklyVarNameByPin('XDualDCMotor'
            , Blockly.getXBlocklyVarPin(dropdownSDAs.value_), Blockly.getXBlocklyVarPin(value)
            , Blockly.getXBlocklyVarPin(dropdownRSTs.value_), Blockly.getXBlocklyVarPin(dropdownSELs.value_)));
        }
        if (value !== null) {
            this.setValue(value);
        }
    };
    dropdownRSTs.onItemSelected = function (menu, menuItem) {
        var value = menuItem.getValue();
        if (this.sourceBlock_) {
            value = this.callValidator(value);
            
            _this.textInputVar.setValue(Blockly.getXBlocklyVarNameByPin('XDualDCMotor'
            , Blockly.getXBlocklyVarPin(dropdownSDAs.value_), Blockly.getXBlocklyVarPin(dropdownSCLs.value_)
            , Blockly.getXBlocklyVarPin(value), Blockly.getXBlocklyVarPin(dropdownSELs.value_)));
        }
        if (value !== null) {
            this.setValue(value);
        }
    };
    dropdownSELs.onItemSelected = function (menu, menuItem) {
        var value = menuItem.getValue();
        if (this.sourceBlock_) {
            value = this.callValidator(value);
            
            _this.textInputVar.setValue(Blockly.getXBlocklyVarNameByPin('XDualDCMotor'
            , Blockly.getXBlocklyVarPin(dropdownSDAs.value_), Blockly.getXBlocklyVarPin(dropdownSCLs.value_)
            , Blockly.getXBlocklyVarPin(dropdownRSTs.value_), Blockly.getXBlocklyVarPin(value)));
        }
        if (value !== null) {
            this.setValue(value);
        }
    };
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XDualDCMotor.png", 16, 16, "*"))
        .appendField(Blockly.Msg.MY_CONSTRUCT_XDUALDCMOTOR);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_MODEL_1)
        .appendField(dropdownModels, "MODEL")
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_MODEL_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_VAR_1)
        .appendField(textInputVar, 'VAR')
        .appendField(Blockly.Msg.MY_CONSTRUCT_XPORTS_VAR_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_PIN_CONNECT);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_PIN_SDA)
        .appendField(dropdownSDAs, "SDA")
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_PIN_SCL)
        .appendField(dropdownSCLs, "SCL")
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_PIN_RST)
        .appendField(dropdownRSTs, "RST")
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_CONSTRUCT_PIN_SEL)
        .appendField(dropdownSELs, "SEL")
        .appendField('');
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'String');
    this.setColour(xblockly_robotColor_construct);
  }
};

Blockly.Blocks.xblockly_xiodriver_digitalRead = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNamePorts([Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      ['S1', '1']
      ,['S2', '2']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIODriver.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIODRIVER_1)
      .appendField(dropdownInstances, "XIODriver")
      .appendField(Blockly.Msg.MY_XIODRIVER_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIODRIVER_INDEX_1)
      .appendField(dropdownIndexs, "INDEX")
      .appendField(Blockly.Msg.MY_XIODRIVER_INDEX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIODRIVER_DIGITALREAD);
    this.setInputsInline(true);
    //this.setPreviousStatement(true, null);
    //this.setNextStatement(true, null);
    this.setOutput(true, Boolean);
    this.setColour(xblockly_robotColor_construct);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xiodriver_analogRead = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNamePorts([Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      ['S1', '1']
      ,['S2', '2']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIODriver.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIODRIVER_1)
      .appendField(dropdownInstances, "XIODriver")
      .appendField(Blockly.Msg.MY_XIODRIVER_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIODRIVER_INDEX_1)
      .appendField(dropdownIndexs, "INDEX")
      .appendField(Blockly.Msg.MY_XIODRIVER_INDEX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIODRIVER_ANALOGREAD);
    this.setInputsInline(true);
    //this.setPreviousStatement(true, null);
    //this.setNextStatement(true, null);
    this.setOutput(true, Boolean);
    this.setColour(xblockly_robotColor_construct);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xiodriver_digitalWrite = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNamePorts([Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      ['S1', '1']
      ,['S2', '2']]);
    var dropdownValues = new Blockly.FieldDropdown([
        ['0', '0']
        ,['1', '1']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIODriver.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIODRIVER_1)
      .appendField(dropdownInstances, "XIODriver")
      .appendField(Blockly.Msg.MY_XIODRIVER_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIODRIVER_INDEX_1)
      .appendField(dropdownIndexs, "INDEX")
      .appendField(Blockly.Msg.MY_XIODRIVER_INDEX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIODRIVER_DIGITALWRITE_1)
      .appendField(dropdownValues, "VALUE")
      .appendField(Blockly.Msg.MY_XIODRIVER_DIGITALWRITE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Boolean');
    this.setColour(xblockly_robotColor_construct);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};


/********************************************
Actuator - 运动模块
*********************************************/

Blockly.Blocks.xblockly_xservo_setAngle = {
  init: function() {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XServo', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XServo.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_SERVO_SETANGLE_1)
        .appendField(dropdownInstances, "XServo")
        .appendField(Blockly.Msg.MY_SERVO_2)
        .appendField(Blockly.Msg.MY_SERVO_SETANGLE_2);
    this.appendValueInput('ANGLE')
        .setCheck(Number);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_SERVO_SETANGLE_ANGLE);
    /*this.appendDummyInput()
        .appendField(new Blockly.FieldAngle(Blockly.Blocks.colour.HUE), 'ANGLE');*/
    this.setInputsInline(true);
    //this.setOutput(true, Number);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
    this.setHelpUrl(Blockly.Msg.MY_SERVO_HELPURL);
    this.setColour(xblockly_robotColor_actuator);
  }
};

Blockly.Blocks.xblockly_xservo_getAngle = {
  init: function() {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XServo', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XServo.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_SERVO_GETANGLE_1)
        .appendField(dropdownInstances, "XServo")
        .appendField(Blockly.Msg.MY_SERVO_2)
        .appendField(Blockly.Msg.MY_SERVO_GETANGLE_2);
    this.setInputsInline(true);
    this.setOutput(true, Number);
    //this.setPreviousStatement(true);
    //this.setNextStatement(true);
    this.setHelpUrl(Blockly.Msg.MY_SERVO_HELPURL);
    this.setColour(xblockly_robotColor_actuator);
  }
};

Blockly.Blocks.xblockly_xdualdcmotor_turn = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XDualDCMotor', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XDUALDCMOTOR_M1, '1']
      ,[Blockly.Msg.MY_XDUALDCMOTOR_M2, '2']
      ,[Blockly.Msg.MY_XDUALDCMOTOR_ALL, '3']]);
    var dropdownDirs = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XDUALDCMOTOR_FORWARD, '0']
      ,[Blockly.Msg.MY_XDUALDCMOTOR_BACKWARD, '1']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XDualDCMotor.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XDUALDCMOTOR_1)
      .appendField(dropdownInstances, "XDualDCMotor")
      .appendField(Blockly.Msg.MY_XDUALDCMOTOR_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XDUALDCMOTOR_TURN_MOTOR_1)
      .appendField(dropdownIndexs, "MOTOR")
      .appendField(Blockly.Msg.MY_XDUALDCMOTOR_TURN_MOTOR_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XDUALDCMOTOR_TURN_DIR_1)
      .appendField(dropdownDirs, "DIR")
      .appendField(Blockly.Msg.MY_XDUALDCMOTOR_TURN_DIR_2)
      .appendField(Blockly.Msg.MY_XDUALDCMOTOR_TURN_SPEED_1);
    this.appendValueInput('SPEED')
      .setCheck(Number);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XDUALDCMOTOR_TURN_SPEED_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(xblockly_robotColor_actuator);
    this.setHelpUrl(Blockly.Msg.MY_XDUALDCMOTOR_HELPURL);
  }
};

Blockly.Blocks.xblockly_xdualdcmotor_stop = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XDualDCMotor', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XDUALDCMOTOR_M1, '1']
      ,[Blockly.Msg.MY_XDUALDCMOTOR_M2, '2']
      ,[Blockly.Msg.MY_XDUALDCMOTOR_ALL, '3']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XDualDCMotor.png", 16, 16, "*"));
        // .appendField(new Blockly.FieldImage("../../media/xblockly/XDualDCMotor.png", 16, 16, "*", 
        // '<rect id="SvgjsRect1009" width="30" height="30" rx="12" ry="12" fill="#ff0066" x="33.5" y="1.5"></rect>'));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XDUALDCMOTOR_1)
      .appendField(dropdownInstances, "XDualDCMotor")
      .appendField(Blockly.Msg.MY_XDUALDCMOTOR_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XDUALDCMOTOR_STOP_MOTOR_1)
      .appendField(dropdownIndexs, "MOTOR")
      .appendField(Blockly.Msg.MY_XDUALDCMOTOR_STOP_MOTOR_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(xblockly_robotColor_actuator);
    this.setHelpUrl(Blockly.Msg.MY_XDUALDCMOTOR_HELPURL);
  }
};

/********************************************
Sensor - 感知模块
*********************************************/

Blockly.Blocks.xblockly_xbutton_isPressed = {
  init: function() {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XButton', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XButton.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUTTON_1)
      .appendField(dropdownInstances, "XButton")
      .appendField(Blockly.Msg.MY_XBUTTON_2)
      .appendField(Blockly.Msg.MY_XBUTTON_ISPRESSED);
    this.setInputsInline(true);
    this.setOutput(true, Boolean);
    //this.setPreviousStatement(true);
    //this.setNextStatement(true);
    this.setHelpUrl(Blockly.Msg.MY_BUTTON_HELPURL);
    this.setColour(xblockly_robotColor_sensor);
  }
};

Blockly.Blocks.xblockly_xbutton_waitPressed = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XButton', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XButton.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUTTON_1)
      .appendField(dropdownInstances, "XButton")
      .appendField(Blockly.Msg.MY_XBUTTON_2)
      .appendField(Blockly.Msg.MY_XBUTTON_WAITPRESSED);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Boolean');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xlightsensor_getLuminance = {
  init: function() {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLightSensor', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLightSensor.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLIGHTSENSOR_1)
      .appendField(dropdownInstances, "XLightSensor")
      .appendField(Blockly.Msg.MY_XLIGHTSENSOR_2)
      .appendField(Blockly.Msg.MY_XLIGHTSENSOR_GETLUMINANCE);
    this.setInputsInline(true);
    this.setOutput(true, Number);
    //this.setPreviousStatement(true);
    //this.setNextStatement(true);
    this.setHelpUrl(Blockly.Msg.MY_LIGHTSENSOR_HELPURL);
    this.setColour(xblockly_robotColor_sensor);
  }
};

Blockly.Blocks.xblockly_xlightsensor_waitLuminance = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLightSensor', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
     ['>', '1']
      , ['<', '2']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLightSensor.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLIGHTSENSOR_1)
      .appendField(dropdownInstances, "XLightSensor")
      .appendField(Blockly.Msg.MY_XLIGHTSENSOR_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLIGHTSENSOR_WAIT_INDEX_1)
      .appendField(dropdownIndexs, 'INDEX')
      .appendField(Blockly.Msg.MY_XLIGHTSENSOR_WAIT_INDEX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLIGHTSENSOR_WAIT_VALUE_1);
    this.appendValueInput('VALUE')
      .setCheck(Number);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLIGHTSENSOR_WAIT_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xsoundsensor_getVolume = {
  init: function() {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XSoundSensor', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XSoundSensor.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XSOUNDSENSOR_1)
      .appendField(dropdownInstances, "XSoundSensor")
      .appendField(Blockly.Msg.MY_XSOUNDSENSOR_2)
      .appendField(Blockly.Msg.MY_XSOUNDSENSOR_GETVOLUME);
    this.setInputsInline(true);
    this.setOutput(true, Number);
    //this.setPreviousStatement(true);
    //this.setNextStatement(true);
    this.setHelpUrl(Blockly.Msg.MY_SOUNDSENSOR_HELPURL);
    this.setColour(xblockly_robotColor_sensor);
  }
};

Blockly.Blocks.xblockly_xsoundsensor_waitVolume = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XSoundSensor', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
     ['>', '1']
      , ['<', '2']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XSoundSensor.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XSOUNDSENSOR_1)
      .appendField(dropdownInstances, "XSoundSensor")
      .appendField(Blockly.Msg.MY_XSOUNDSENSOR_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XSOUNDSENSOR_WAIT_INDEX_1)
      .appendField(dropdownIndexs, 'INDEX')
      .appendField(Blockly.Msg.MY_XSOUNDSENSOR_WAIT_INDEX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XSOUNDSENSOR_WAIT_VALUE_1);
    this.appendValueInput('VALUE')
      .setCheck(Number);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XSOUNDSENSOR_WAIT_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xirtracking_hasStatus = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XIRTracking',[Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownStatus = new Blockly.FieldDropdown([
      ['■■', '3']
      , ['■□', '1']
      , ['□■', '2']
      , ['□□', '0']
      ]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIRTracking.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_1)
      .appendField(dropdownInstances, "XIRTracking")
      .appendField(Blockly.Msg.MY_XIRTRACKING_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_HASSTATUS_1)
      .appendField(dropdownStatus, "STATUS")
      .appendField(Blockly.Msg.MY_XIRTRACKING_HASSTATUS_2);
    this.setInputsInline(true);
    //this.setPreviousStatement(true, null);
    //this.setNextStatement(true, null);
    this.setOutput(true, Boolean);
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xirtracking_waitStatus = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XIRTracking', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      ['=', '1']
      , ['\u2260', '2']
      ]);
    var dropdownStatus = new Blockly.FieldDropdown([
      ['■■', '3']
      , ['■□', '1']
      , ['□■', '2']
      , ['□□', '0']
      ]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIRTracking.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_1)
      .appendField(dropdownInstances, "XIRTracking")
      .appendField(Blockly.Msg.MY_XIRTRACKING_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_WAIT_INDEX_1)
      .appendField(dropdownIndexs, 'INDEX')
      .appendField(Blockly.Msg.MY_XIRTRACKING_WAIT_INDEX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_WAIT_STATUS_1)
      .appendField(dropdownStatus, "STATUS")
      .appendField(Blockly.Msg.MY_XIRTRACKING_WAIT_STATUS_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};


Blockly.Blocks.xblockly_xirtracking6_hasStatus = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XIRTracking6',[Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownStatus1 = new Blockly.FieldDropdown([
      ['■', '1']
      , ['□', '0']
    ]);
    var dropdownStatus2 = new Blockly.FieldDropdown([
      ['■', '2']
      , ['□', '0']
    ]);
    var dropdownStatus3 = new Blockly.FieldDropdown([
      ['■', '4']
      , ['□', '0']
    ]);
    var dropdownStatus4 = new Blockly.FieldDropdown([
      ['■', '8']
      , ['□', '0']
    ]);
    var dropdownStatus5 = new Blockly.FieldDropdown([
      ['■', '16']
      , ['□', '0']
    ]);
    var dropdownStatus6 = new Blockly.FieldDropdown([
      ['■', '32']
      , ['□', '0']
    ]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIRTracking.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING6_1)
      .appendField(dropdownInstances, "XIRTracking6")
      .appendField(Blockly.Msg.MY_XIRTRACKING6_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_HASSTATUS_1)
      .appendField(Blockly.Msg.MY_XIRTRACKING_S1_1)
      .appendField(dropdownStatus1, "S1")
      .appendField(Blockly.Msg.MY_XIRTRACKING_S1_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_S2_1)
      .appendField(dropdownStatus2, "S2")
      .appendField(Blockly.Msg.MY_XIRTRACKING_S2_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_S3_1)
      .appendField(dropdownStatus3, "S3")
      .appendField(Blockly.Msg.MY_XIRTRACKING_S3_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_S4_1)
      .appendField(dropdownStatus4, "S4")
      .appendField(Blockly.Msg.MY_XIRTRACKING_S4_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_S5_1)
      .appendField(dropdownStatus5, "S5")
      .appendField(Blockly.Msg.MY_XIRTRACKING_S5_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_S6_1)
      .appendField(dropdownStatus6, "S6")
      .appendField(Blockly.Msg.MY_XIRTRACKING_S6_2);
    this.setInputsInline(true);
    //this.setPreviousStatement(true, null);
    //this.setNextStatement(true, null);
    this.setOutput(true, Boolean);
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xirtracking6_waitStatus = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XIRTracking6', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      ['=', '1']
      , ['\u2260', '2']
    ]);
    var dropdownStatus1 = new Blockly.FieldDropdown([
      ['■', '1']
      , ['□', '0']
    ]);
    var dropdownStatus2 = new Blockly.FieldDropdown([
      ['■', '2']
      , ['□', '0']
    ]);
    var dropdownStatus3 = new Blockly.FieldDropdown([
      ['■', '4']
      , ['□', '0']
    ]);
    var dropdownStatus4 = new Blockly.FieldDropdown([
      ['■', '8']
      , ['□', '0']
    ]);
    var dropdownStatus5 = new Blockly.FieldDropdown([
      ['■', '16']
      , ['□', '0']
    ]);
    var dropdownStatus6 = new Blockly.FieldDropdown([
      ['■', '32']
      , ['□', '0']
    ]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIRTracking.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING6_1)
      .appendField(dropdownInstances, "XIRTracking6")
      .appendField(Blockly.Msg.MY_XIRTRACKING6_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_WAIT_INDEX_1)
      .appendField(dropdownIndexs, 'INDEX')
      .appendField(Blockly.Msg.MY_XIRTRACKING_WAIT_INDEX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_S1_1)
      .appendField(dropdownStatus1, "S1")
      .appendField(Blockly.Msg.MY_XIRTRACKING_S1_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_S2_1)
      .appendField(dropdownStatus2, "S2")
      .appendField(Blockly.Msg.MY_XIRTRACKING_S2_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_S3_1)
      .appendField(dropdownStatus3, "S3")
      .appendField(Blockly.Msg.MY_XIRTRACKING_S3_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_S4_1)
      .appendField(dropdownStatus4, "S4")
      .appendField(Blockly.Msg.MY_XIRTRACKING_S4_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_S5_1)
      .appendField(dropdownStatus5, "S5")
      .appendField(Blockly.Msg.MY_XIRTRACKING_S5_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRTRACKING_S6_1)
      .appendField(dropdownStatus6, "S6")
      .appendField(Blockly.Msg.MY_XIRTRACKING_S6_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xultrasonic_getDistance = {
  init: function() {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XUltrasonic', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XUltrasonic.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XULTRASONIC_GETDISTANCE_1)
        .appendField(dropdownInstances, "XUltrasonic")
        .appendField(Blockly.Msg.MY_XULTRASONIC_2)
        .appendField(Blockly.Msg.MY_XULTRASONIC_GETDISTANCE_2);
    this.setInputsInline(true);
    this.setOutput(true, Number);
    //this.setPreviousStatement(true);
    //this.setNextStatement(true);
    this.setHelpUrl(Blockly.Msg.MY_XULTRASONIC_HELPURL);
    this.setColour(xblockly_robotColor_sensor);
  }
};

Blockly.Blocks.xblockly_xultrasonic_waitDistance = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XUltrasonic', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
     ['>', '1']
      , ['<', '2']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XUltrasonic.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XULTRASONIC_1)
      .appendField(dropdownInstances, "XUltrasonic")
      .appendField(Blockly.Msg.MY_XULTRASONIC_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XULTRASONIC_WAIT_INDEX_1)
      .appendField(dropdownIndexs, 'INDEX')
      .appendField(Blockly.Msg.MY_XULTRASONIC_WAIT_INDEX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XULTRASONIC_WAIT_VALUE_1);
    this.appendValueInput('VALUE')
      .setCheck(Number);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XULTRASONIC_WAIT_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xiravoiding_start = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XIRAvoiding', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIRAvoiding.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XIRAVOIDING_1)
        .appendField(dropdownInstances, "XIRAvoiding")
        .appendField(Blockly.Msg.MY_XIRAVOIDING_2)
        .appendField(Blockly.Msg.MY_XIRAVOIDING_START);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XIRAVOIDING_START_SENSITIVE_1);
    this.appendValueInput('SENSITIVE')
        .setCheck(Number);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XIRAVOIDING_START_SENSITIVE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Boolean');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xiravoiding_stop = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XIRAvoiding', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIRAvoiding.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XIRAVOIDING_1)
        .appendField(dropdownInstances, "XIRAvoiding")
        .appendField(Blockly.Msg.MY_XIRAVOIDING_2)
        .appendField(Blockly.Msg.MY_XIRAVOIDING_STOP);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Boolean');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xiravoiding_getStatus = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XIRAvoiding',[Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIRAvoiding.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRAVOIDING_1)
      .appendField(dropdownInstances, "XIRAvoiding")
      .appendField(Blockly.Msg.MY_XIRAVOIDING_2)
      .appendField(Blockly.Msg.MY_XIRAVOIDING_GETSTATUS);
    this.setInputsInline(true);
    //this.setPreviousStatement(true, null);
    //this.setNextStatement(true, null);
    this.setOutput(true, Boolean);
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xiravoiding_waitStatus = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XIRAvoiding', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownEvents = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XIRAVOIDING_EVENT_with, '1']
      ,[Blockly.Msg.MY_XIRAVOIDING_EVENT_no, '2']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIRAvoiding.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRAVOIDING_1)
      .appendField(dropdownInstances, "XIRAvoiding")
      .appendField(Blockly.Msg.MY_XIRAVOIDING_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRAVOIDING_WAITSTATUS_1)
      .appendField(dropdownEvents, "EVENT")
      .appendField(Blockly.Msg.MY_XIRAVOIDING_WAITSTATUS_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Boolean');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xpotentiometer_getValue = {
  init: function() {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XPotentiometer', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XPotentiometer.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XPOTENTIOMETER_1)
        .appendField(dropdownInstances, "XPotentiometer")
        .appendField(Blockly.Msg.MY_XPOTENTIOMETER_2)
        .appendField(Blockly.Msg.MY_XPOTENTIOMETER_GETVALUE);
    this.setInputsInline(true);
    this.setOutput(true, Number);
    //this.setPreviousStatement(true);
    //this.setNextStatement(true);
    this.setColour(xblockly_robotColor_sensor);
  }
};

Blockly.Blocks.xblockly_xpotentiometer_waitValue = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XPotentiometer', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
     ['>', '1']
      , ['<', '2']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XPotentiometer.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XPOTENTIOMETER_1)
      .appendField(dropdownInstances, "XPotentiometer")
      .appendField(Blockly.Msg.MY_XPOTENTIOMETER_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XPOTENTIOMETER_WAIT_INDEX_1)
      .appendField(dropdownIndexs, 'INDEX')
      .appendField(Blockly.Msg.MY_XPOTENTIOMETER_WAIT_INDEX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XPOTENTIOMETER_WAIT_VALUE_1);
    this.appendValueInput('VALUE')
      .setCheck(Number);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XPOTENTIOMETER_WAIT_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xhumiture_getHumidity = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XHumiture', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XDHT.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XHUMITURE_1)
      .appendField(dropdownInstances, "XHumiture")
      .appendField(Blockly.Msg.MY_XHUMITURE_2)
      .appendField(Blockly.Msg.MY_XHUMITURE_GETHUMIDITY);
    this.setInputsInline(true);
    //this.setPreviousStatement(true, null);
    //this.setNextStatement(true, null);
    this.setOutput(true, Number);
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xhumiture_getTemperature = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XHumiture', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XDHT.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XHUMITURE_1)
      .appendField(dropdownInstances, "XHumiture")
      .appendField(Blockly.Msg.MY_XHUMITURE_2)
      .appendField(Blockly.Msg.MY_XHUMITURE_GETTEMPERATURE);
    this.setInputsInline(true);
    //this.setPreviousStatement(true, null);
    //this.setNextStatement(true, null);
    this.setOutput(true, Number);
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xhumiture_waitHumidity = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XHumiture', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
     ['>', '1']
      , ['<', '2']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XDHT.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XHUMITURE_1)
      .appendField(dropdownInstances, "XHumiture")
      .appendField(Blockly.Msg.MY_XHUMITURE_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XHUMITURE_WAITHUMIDITY_INDEX_1)
      .appendField(dropdownIndexs, 'INDEX')
      .appendField(Blockly.Msg.MY_XHUMITURE_WAITHUMIDITY_INDEX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XHUMITURE_WAITHUMIDITY_VALUE_1);
    this.appendValueInput('VALUE')
      .setCheck(Number);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XHUMITURE_WAITHUMIDITY_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, Number);
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xhumiture_waitTemperature = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XHumiture', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
     ['>', '3']
      , ['<', '4']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XDHT.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XHUMITURE_1)
      .appendField(dropdownInstances, "XHumiture")
      .appendField(Blockly.Msg.MY_XHUMITURE_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XHUMITURE_WAITTEMPERATURE_INDEX_1)
      .appendField(dropdownIndexs, 'INDEX')
      .appendField(Blockly.Msg.MY_XHUMITURE_WAITTEMPERATURE_INDEX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XHUMITUREWAITTEMPERATURE_VALUE_1);
    this.appendValueInput('VALUE')
      .setCheck(Number);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XHUMITURE_WAITTEMPERATURE_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xpir_isMotionDetected = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XPIR', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XPIR.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XPIR_1)
        .appendField(dropdownInstances, "XPIR")
        .appendField(Blockly.Msg.MY_XPIR_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XPIR_ISMOTIONDETECTED);
    this.setInputsInline(true);
    //this.setPreviousStatement(true, null);
    //this.setNextStatement(true, null);
    this.setOutput(true, Boolean);
    this.setHelpUrl(Blockly.Msg.MY_XPIR_HELPURL);
    this.setColour(xblockly_robotColor_sensor);
  }
};

Blockly.Blocks.xblockly_xpir_waitMotion = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XPIR', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
     [Blockly.Msg.MY_XPIR_EVENT_with, '1']
      , [Blockly.Msg.MY_XPIR_EVENT_no, '2']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XPIR.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XPIR_1)
      .appendField(dropdownInstances, "XPIR")
      .appendField(Blockly.Msg.MY_XPIR_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XPIR_WAIT_INDEX_1)
      .appendField(dropdownIndexs, 'INDEX')
      .appendField(Blockly.Msg.MY_XPIR_WAIT_INDEX_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xshocksensor_isShocking = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XShockSensor',[Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XShockSensor.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XSHOCKSENSOR_1)
      .appendField(dropdownInstances, "XShockSensor")
      .appendField(Blockly.Msg.MY_XSHOCKSENSOR_2)
      .appendField(Blockly.Msg.MY_XSHOCKSENSOR_ISSHOCKING);
    this.setInputsInline(true);
    //this.setPreviousStatement(true, null);
    //this.setNextStatement(true, null);
    this.setOutput(true, Boolean);
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  },
  /** Assigns a type to the boolean block. */
  getBlockType: function() {
    return Blockly.Types.BOOLEAN;
  }
};

Blockly.Blocks.xblockly_xshocksensor_waitStatus = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XShockSensor', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownEvents = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XSHOCKSENSOR_EVENT_with, '1']
      ,[Blockly.Msg.MY_XSHOCKSENSOR_EVENT_no, '2']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XShockSensor.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XSHOCKSENSOR_1)
      .appendField(dropdownInstances, "XShockSensor")
      .appendField(Blockly.Msg.MY_XSHOCKSENSOR_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XSHOCKSENSOR_WAITSTATUS_1)
      .appendField(dropdownEvents, "EVENT")
      .appendField(Blockly.Msg.MY_XSHOCKSENSOR_WAITSTATUS_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Boolean');
    this.setColour(xblockly_robotColor_sensor);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

/********************************************
Display - 展示模块
*********************************************/

Blockly.Blocks.xblockly_xsegdisplay_showNumber = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XSegDisplay', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownFormats = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XSEGDISPLAY_FORMAT_DEC, '10']
      , [Blockly.Msg.MY_XSEGDISPLAY_FORMAT_HEX, '16']
      , [Blockly.Msg.MY_XSEGDISPLAY_FORMAT_BIN, '2']
      ]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XSegDisplay.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_1)
        .appendField(dropdownInstances, "XSegDisplay")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_2);
    this.appendValueInput('VALUE')
        .setCheck(Number)
        //.setAlign(Blockly.ALIGN_LEFT)
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWNUMBER_1);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWNUMBER_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xsegdisplay_showNumberEx = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XSegDisplay', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownFormats = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XSEGDISPLAY_FORMAT_DEC, '10']
      , [Blockly.Msg.MY_XSEGDISPLAY_FORMAT_HEX, '16']
      , [Blockly.Msg.MY_XSEGDISPLAY_FORMAT_BIN, '2']
      ]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XSegDisplay.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_1)
        .appendField(dropdownInstances, "XSegDisplay")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_2);
    this.appendValueInput('VALUE')
        .setCheck(Number)
        //.setAlign(Blockly.ALIGN_LEFT)
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWNUMBER_1);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWNUMBEREX_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWNUMBER_FORMAT_1)
        .appendField(dropdownFormats, "FORMAT")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWNUMBER_FORMAT_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xsegdisplay_showCharacter = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XSegDisplay', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XSEGDISPLAY_INDEX_1, '1']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_2, '2']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_3, '3']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_4, '4']
      ]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XSegDisplay.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_1)
        .appendField(dropdownInstances, "XSegDisplay")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWCHARACTER_INDEX_1)
        .appendField(dropdownIndexs, "INDEX")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWCHARACTER_INDEX_2);
    this.appendValueInput('VALUE')
        .setCheck(Number)
        //.setAlign(Blockly.ALIGN_LEFT)
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWCHARACTER_VALUE_1);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWCHARACTER_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xsegdisplay_showSegment = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XSegDisplay', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XSEGDISPLAY_INDEX_1, '1']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_2, '2']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_3, '3']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_4, '4']
    ]);
    var dropdownSegments = new Blockly.FieldDropdown([
      ['a', 'a']
      , ['b', 'b']
      , ['c', 'c']
      , ['d', 'd']
      , ['e', 'e']
      , ['f', 'f']
      , ['g', 'g']
      , ['.', '.']
    ]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XSegDisplay.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_1)
        .appendField(dropdownInstances, "XSegDisplay")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWSEGMENT_INDEX_1)
        .appendField(dropdownIndexs, "INDEX")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWSEGMENT_INDEX_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWSEGMENT_VALUE_1)
        .appendField(dropdownSegments, "VALUE")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_SHOWSEGMENT_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xsegdisplay_clearSegment = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XSegDisplay', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XSEGDISPLAY_INDEX_1, '1']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_2, '2']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_3, '3']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_4, '4']
    ]);
    var dropdownSegments = new Blockly.FieldDropdown([
      ['a', 'a']
      , ['b', 'b']
      , ['c', 'c']
      , ['d', 'd']
      , ['e', 'e']
      , ['f', 'f']
      , ['g', 'g']
      , ['.', '.']
    ]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XSegDisplay.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_1)
        .appendField(dropdownInstances, "XSegDisplay")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_CLEARSEGMENT_INDEX_1)
        .appendField(dropdownIndexs, "INDEX")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_CLEARSEGMENT_INDEX_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_CLEARSEGMENT_VALUE_1)
        .appendField(dropdownSegments, "VALUE")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_CLEARSEGMENT_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xsegdisplay_clear = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XSegDisplay', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XSEGDISPLAY_INDEX_ALL, '0']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_1, '1']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_2, '2']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_3, '3']
      , [Blockly.Msg.MY_XSEGDISPLAY_INDEX_4, '4']
      ]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XSegDisplay.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_1)
        .appendField(dropdownInstances, "XSegDisplay")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_CLEAR_INDEX_1)
        .appendField(dropdownIndexs, "INDEX")
        .appendField(Blockly.Msg.MY_XSEGDISPLAY_CLEAR_INDEX_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xledmatrix_move = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLEDMatrix', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLEDMatrix.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XLEDMATRIX_1)
        .appendField(dropdownInstances, "XLEDMatrix")
        .appendField(Blockly.Msg.MY_XLEDMATRIX_2)
        .appendField(Blockly.Msg.MY_XLEDMATRIX_MOVE);
    this.appendValueInput('X')
        .setCheck(Number)
        .appendField(Blockly.Msg.MY_XLEDMATRIX_MOVE_X_1);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XLEDMATRIX_MOVE_X_2);
    this.appendValueInput('Y')
        .setCheck(Number)
        .appendField(Blockly.Msg.MY_XLEDMATRIX_MOVE_Y_1);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XLEDMATRIX_MOVE_Y_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xledmatrix_setBrightness = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLEDMatrix', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownValues = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XLEDMATRIX_BRIGHTNESS_0, '0']
      , [Blockly.Msg.MY_XLEDMATRIX_BRIGHTNESS_1, '1']
      , [Blockly.Msg.MY_XLEDMATRIX_BRIGHTNESS_2, '2']
      , [Blockly.Msg.MY_XLEDMATRIX_BRIGHTNESS_3, '3']
      , [Blockly.Msg.MY_XLEDMATRIX_BRIGHTNESS_4, '4']
      , [Blockly.Msg.MY_XLEDMATRIX_BRIGHTNESS_5, '5']
      , [Blockly.Msg.MY_XLEDMATRIX_BRIGHTNESS_6, '6']
      , [Blockly.Msg.MY_XLEDMATRIX_BRIGHTNESS_7, '7']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLEDMatrix.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XLEDMATRIX_1)
        .appendField(dropdownInstances, "XLEDMatrix")
        .appendField(Blockly.Msg.MY_XLEDMATRIX_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XLEDMATRIX_SETBRIGHTNESS_VALUE_1)
        .appendField(dropdownValues, "VALUE")
        .appendField(Blockly.Msg.MY_XLEDMATRIX_SETBRIGHTNESS_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xledmatrix_setColorInverse = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLEDMatrix', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownValues = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XLEDMATRIX_COLORINVERSE_NORMAL, '0']
       , [Blockly.Msg.MY_XLEDMATRIX_COLORINVERSE_INVERSE, '1']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLEDMatrix.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XLEDMATRIX_1)
        .appendField(dropdownInstances, "XLEDMatrix")
        .appendField(Blockly.Msg.MY_XLEDMATRIX_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XLEDMATRIX_SETCOLORINVERSE_VALUE_1)
        .appendField(dropdownValues, "VALUE")
        .appendField(Blockly.Msg.MY_XLEDMATRIX_SETCOLORINVERSE_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xledmatrix_setEffect = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLEDMatrix', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownEffects = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XLEDMATRIX_EFFECT_STATIC, '0']
      , [Blockly.Msg.MY_XLEDMATRIX_EFFECT_UP, '1']
      , [Blockly.Msg.MY_XLEDMATRIX_EFFECT_DOWN, '2']
       , [Blockly.Msg.MY_XLEDMATRIX_EFFECT_LEFT, '3']
       , [Blockly.Msg.MY_XLEDMATRIX_EFFECT_RIGHT, '4']
       , [Blockly.Msg.MY_XLEDMATRIX_EFFECT_FLICKER, '5']]);
    var dropdownSpeeds = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XLEDMATRIX_SPEED_SLOW, '0']
       , [Blockly.Msg.MY_XLEDMATRIX_SPEED_MIDDLE, '1']
       , [Blockly.Msg.MY_XLEDMATRIX_SPEED_FAST, '2']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLEDMatrix.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_1)
      .appendField(dropdownInstances, "XLEDMatrix")
      .appendField(Blockly.Msg.MY_XLEDMATRIX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SETEFFECT_EFFECT_1)
      .appendField(dropdownEffects, "EFFECT")
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SETEFFECT_EFFECT_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SETEFFECT_SPEED_1)
      .appendField(dropdownSpeeds, "SPEED")
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SETEFFECT_SPEED_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

// 自定义 图形化
Blockly.Blocks.xblockly_xledmatrix_matrix = { //
  init: function() {
    this.setColour(xblockly_robotColor_display);
    for(var row = 0 ; row < 8; row ++) {
      var leds = this.appendDummyInput();
      for (var col = 0; col < 16; col++) {
          var cbox = new Blockly.FieldCheckbox(false);
          leds.appendField(cbox, row + '_' + col);
      }
    }
    this.setOutput(true, String);
    this.setTooltip('');
  }
};

Blockly.Blocks.xblockly_xledmatrix_showBitmap = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLEDMatrix', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLEDMatrix.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_1)
      .appendField(dropdownInstances, "XLEDMatrix")
      .appendField(Blockly.Msg.MY_XLEDMATRIX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWBITMAP_VALUE_1);
    this.appendValueInput('VALUE')
      .setCheck(String)
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWBITMAP_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xledmatrix_showNumber = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLEDMatrix', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLEDMatrix.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_1)
      .appendField(dropdownInstances, "XLEDMatrix")
      .appendField(Blockly.Msg.MY_XLEDMATRIX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWNUMBER_NUM_1);
    this.appendValueInput('NUM')
      .setCheck(Number)
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWNUMBER_NUM_2);
    /*this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWNUMBER_X_1);
    this.appendValueInput('X')
      .setCheck(Number)
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWNUMBER_X_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWNUMBER_Y_1);
    this.appendValueInput('Y')
      .setCheck(Number)
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWNUMBER_Y_2);*/
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xledmatrix_showNumberPair = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLEDMatrix', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLEDMatrix.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_1)
      .appendField(dropdownInstances, "XLEDMatrix")
      .appendField(Blockly.Msg.MY_XLEDMATRIX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWSCORE_A_1);
    this.appendValueInput('A')
      .setCheck(Number)
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWSCORE_A_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWSCORE_B_1);
    this.appendValueInput('B')
      .setCheck(Number)
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWSCORE_B_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xledmatrix_showString = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLEDMatrix', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLEDMatrix.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_1)
      .appendField(dropdownInstances, "XLEDMatrix")
      .appendField(Blockly.Msg.MY_XLEDMATRIX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWSTRING_VALUE_1);
    this.appendValueInput('VALUE')
      .setCheck(String)
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWSTRING_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xledmatrix_showEmoticon = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLEDMatrix', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownEmotions = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XLEDMATRIX_EMOTION_COOL, '0']
      , [Blockly.Msg.MY_XLEDMATRIX_EMOTION_SMILE, '1']
      , [Blockly.Msg.MY_XLEDMATRIX_EMOTION_LAUGH, '2']
      , [Blockly.Msg.MY_XLEDMATRIX_EMOTION_GRIEVANCE, '3']
      , [Blockly.Msg.MY_XLEDMATRIX_EMOTION_ANGRY, '4']
      , [Blockly.Msg.MY_XLEDMATRIX_EMOTION_ANGER, '5']
      , [Blockly.Msg.MY_XLEDMATRIX_EMOTION_CRY, '6']
      , [Blockly.Msg.MY_XLEDMATRIX_EMOTION_NAUGHTY, '7']
       , [Blockly.Msg.MY_XLEDMATRIX_EMOTION_LOVE, '8']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLEDMatrix.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_1)
      .appendField(dropdownInstances, "XLEDMatrix")
      .appendField(Blockly.Msg.MY_XLEDMATRIX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWEMOTION_VALUE_1)
      .appendField(dropdownEmotions, "EMOTION")
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWEMOTION_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xledmatrix_showFlag = {
  init: function () {
    var _this = this;
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLEDMatrix', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    
    function getMyIndexs() {
      return [[Blockly.Msg.MY_XLEDMATRIX_FLAG_DIRECTION, '1']
          ,[Blockly.Msg.MY_XLEDMATRIX_FLAG_OTHER, '2']];
    }
    var dropdownIndexs = this.dropdownIndexs = new Blockly.FieldDropdown(getMyIndexs);
    this.getMyValues = function () {
        switch(dropdownIndexs.value_)
        {
            case '1': {
                return [
                  [Blockly.Msg.MY_XLEDMATRIX_FLAG_UP, '4']
                    , [Blockly.Msg.MY_XLEDMATRIX_FLAG_DOWN, '5']
                    , [Blockly.Msg.MY_XLEDMATRIX_FLAG_LEFT, '6']
                    , [Blockly.Msg.MY_XLEDMATRIX_FLAG_RIGHT, '7']
                    , [Blockly.Msg.MY_XLEDMATRIX_FLAG_STOP, '8']
                    , [Blockly.Msg.MY_XLEDMATRIX_FLAG_FORWARD_LEFT, '9']
                    , [Blockly.Msg.MY_XLEDMATRIX_FLAG_FORWARD_RIGHT, '10']
                    , [Blockly.Msg.MY_XLEDMATRIX_FLAG_BACKWARD_LEFT, '11']
                    , [Blockly.Msg.MY_XLEDMATRIX_FLAG_BACKWARD_RIGHT, '12']
                ];
            }
            break;
            case '2': {
                return [
                  [Blockly.Msg.MY_XLEDMATRIX_FLAG_X, '0']
                  , [Blockly.Msg.MY_XLEDMATRIX_FLAG_RECTANGLE, '1']
                  , [Blockly.Msg.MY_XLEDMATRIX_FLAG_TRIGANLE, '2']
                  , [Blockly.Msg.MY_XLEDMATRIX_FLAG_CIRCLE, '3']
                  , [Blockly.Msg.MY_XLEDMATRIX_FLAG_CUP, '13']
                  , [Blockly.Msg.MY_XLEDMATRIX_FLAG_BANNER, '14']
                ];
            }
            break;
            default: {
                return [[Blockly.Msg.MY_NULL, '']];
            }
            break;
        }
    }
    var dropdownValues = this.dropdownValues = new Blockly.FieldDropdown(this.getMyValues);
    dropdownIndexs.onItemSelected = function (menu, menuItem) {
        var value = menuItem.getValue();
        if (this.sourceBlock_) {
            // Call any validation function, and allow it to override.
            value = this.callValidator(value);
        }
        if (value !== null) {
            this.setValue(value);

            var values = _this.getMyValues();
            _this.dropdownValues.setValue(values[0][1]);
        }
    };
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLEDMatrix.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_1)
      .appendField(dropdownInstances, "XLEDMatrix")
      .appendField(Blockly.Msg.MY_XLEDMATRIX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWFLAG_INDEX_1)
      .appendField(dropdownIndexs, 'INDEX')
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWFLAG_INDEX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWFLAG_VALUE_1)
      .appendField(dropdownValues, "VALUE")
      .appendField(Blockly.Msg.MY_XLEDMATRIX_SHOWFLAG_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }/*,

  onchange: function () {
    if (!this.workspace) return;  // Block has been deleted.

    if (this.isInFlyout) return;
  
    if (this.isInMutator) return;

    //var index = this.getFieldValue('INDEX')-1;
    var value = this.getFieldValue('VALUE');
    var values = this.getMyValues();
    for(var i=0; i<values.length; i++)
    {
      if(value == values[i][1]) {
        break;
      }
    }
    if (i >= values.length) {
      value = values[0][1];
      this.dropdownValues.setValue(value);
    }
  }*/
};

Blockly.Blocks.xblockly_xledmatrix_clear = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XLEDMatrix', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XLEDMatrix.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_1)
      .appendField(dropdownInstances, "XLEDMatrix")
      .appendField(Blockly.Msg.MY_XLEDMATRIX_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XLEDMATRIX_CLEAR);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xvoicebroadcast_reportObject = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XVoiceBroadcast', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XYGRVoiceBroadcast_Object_VALUE, '0']
      ,[Blockly.Msg.MY_XYGRVoiceBroadcast_Object_LIGHT, '1']
      ,[Blockly.Msg.MY_XYGRVoiceBroadcast_Object_SOUND, '2']
      ,[Blockly.Msg.MY_XYGRVoiceBroadcast_Object_TEMPERATURE, '3']
      ,[Blockly.Msg.MY_XYGRVoiceBroadcast_Object_HUMIDITY, '4']
      ,[Blockly.Msg.MY_XYGRVoiceBroadcast_Object_DISTANCE, '5']
      ,[Blockly.Msg.MY_XYGRVoiceBroadcast_Object_SPEED, '6']
      ,[Blockly.Msg.MY_XYGRVoiceBroadcast_Object_STATUS, '7']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XVoiceBroadcast.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_1)
        .appendField(dropdownInstances, "XVoiceBroadcast")
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTOBJECT_INDEX_1)
        .appendField(dropdownIndexs, 'INDEX')
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTOBJECT_INDEX_2)
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTOBJECT_VALUE_1);
    this.appendValueInput('VALUE')
        .setCheck(Number)
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTOBJECT_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xvoicebroadcast_reportTime = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XVoiceBroadcast', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XVoiceBroadcast.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_1)
        .appendField(dropdownInstances, "XVoiceBroadcast")
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTTIME_HOUR_1);
    this.appendValueInput('HOUR')
        .setCheck(Number);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTTIME_HOUR_2)
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTTIME_MINUTE_1);
    this.appendValueInput('MINUTE')
        .setCheck(Number);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTTIME_MINUTE_2)
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTTIME_SECOND_1);
    this.appendValueInput('SECOND')
        .setCheck(Number);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTTIME_SECOND_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xvoicebroadcast_reportDate = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XVoiceBroadcast', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    /*var dropdownWeekDays = new Blockly.FieldDropdown([
        [Blockly.Msg.MY_XYGRVOICEBROADCAST_WEEK_1, '0']
        ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_WEEK_2, '1']
        ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_WEEK_3, '2']
        ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_WEEK_4, '3']
        ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_WEEK_5, '4']
        ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_WEEK_6, '5']
        ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_WEEK_7, '6']]);*/
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XVoiceBroadcast.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_1)
        .appendField(dropdownInstances, "XVoiceBroadcast")
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTDATE_YEAR_1);
    this.appendValueInput('YEAR')
        .setCheck(Number);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTDATE_YEAR_2)
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTDATE_MONTH_1);
    this.appendValueInput('MONTH')
        .setCheck(Number);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTDATE_MONTH_2)
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTDATE_DAY_1);
    this.appendValueInput('DAY')
        .setCheck(Number);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTDATE_DAY_2)
        /*.appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTDATE_WEEKDAY_1)
        .appendField(dropdownWeekDays, "WEEKDAY")
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTDATE_WEEKDAY_2)*/;
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xvoicebroadcast_reportOperator = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XVoiceBroadcast', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownIndexs = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XYGRVoiceBroadcast_Operator_ADD, '61']
      ,[Blockly.Msg.MY_XYGRVoiceBroadcast_Operator_MINUS, '62']
      ,[Blockly.Msg.MY_XYGRVoiceBroadcast_Operator_MULTI, '63']
      ,[Blockly.Msg.MY_XYGRVoiceBroadcast_Operator_DIVIDE, '64']
      ,[Blockly.Msg.MY_XYGRVoiceBroadcast_Operator_EQUAL, '65']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XVoiceBroadcast.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_1)
        .appendField(dropdownInstances, "XVoiceBroadcast")
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTOPERATOR_INDEX_1)
        .appendField(dropdownIndexs, 'INDEX')
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTOPERATOR_INDEX_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xvoicebroadcast_reportSound = {
  init: function () {
    var _this = this;
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XVoiceBroadcast', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    function getMyIndexs() {
        return [
            [Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_ACTION, '0']
            ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_ALARM, '1']
            ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_SCIENCE, '2']
            ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_WARN, '3']
            ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_OUTSTAR, '4']
            ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_MOOD, '5']
            ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_MUSIC, '6']];
    }
    var dropdownIndexs = this.dropdownIndexs = new Blockly.FieldDropdown(getMyIndexs);
    this.getMyValues = function () {
        switch(dropdownIndexs.value_)
        {
            case '0': {
                return [
                    [Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_70, '70']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_71, '71']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_72, '72']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_73, '73']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_74, '74']
                ];
            }
            break;
            case '1': {
                return [
                    [Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_78, '78']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_79, '79']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_80, '80']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_81, '81']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_82, '82']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_83, '83']
                ];
            }
            break;
            case '2': {
                return [
                    [Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_86, '86']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_87, '87']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_88, '88']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_89, '89']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_90, '90']
                ];
            }
            break;
            case '3': {
                return [
                    [Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_94, '94']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_95, '95']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_96, '96']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_97, '97']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_98, '98']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_99, '99']
                ];
            }
            break;
            case '4': {
                return [
                    [Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_102, '102']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_103, '103']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_104, '104']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_105, '105']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_106, '106']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_107, '107']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_108, '108']
                ];
            }
            break;
            case '5': {
                return [
                    [Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_110, '110']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_111, '111']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_112, '112']
                ];
            }
            break;
            case '6': {
                return [
                    [Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_118, '118']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_119, '119']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_120, '120']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_121, '121']
                    ,[Blockly.Msg.MY_XYGRVOICEBROADCAST_SOUND_EFFECT_122, '122']
                ];
            }
            break;
            default: {
                return [[Blockly.Msg.MY_NULL, '']];
            }
            break;
        }
    }
    var dropdownValues = this.dropdownValues = new Blockly.FieldDropdown(this.getMyValues);
    dropdownIndexs.onItemSelected = function (menu, menuItem) {
        var value = menuItem.getValue();
        if (this.sourceBlock_) {
            // Call any validation function, and allow it to override.
            value = this.callValidator(value);
        }
        if (value !== null) {
            this.setValue(value);

            var values = _this.getMyValues();
            _this.dropdownValues.setValue(values[0][1]);
        }
    };
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XVoiceBroadcast.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_1)
        .appendField(dropdownInstances, "XVoiceBroadcast")
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTSOUND_INDEX_1)
        .appendField(dropdownIndexs, 'INDEX')
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTSOUND_INDEX_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTSOUND_VALUE_1)
        .appendField(dropdownValues, 'VALUE')
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTSOUND_VALUE_2);
    this.appendDummyInput()
        .appendField(new Blockly.FieldCheckbox('FALSE'), 'REPEAT')
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_REPORTSOUND_REPEAT);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }/*,

  onchange: function () {
    if (!this.workspace) return;  // Block has been deleted.

    if (this.isInFlyout) return;
  
    if (this.isInMutator) return;

    //var index = this.getFieldValue('INDEX')-1;
    var value = this.getFieldValue('VALUE');
    var values = this.getMyValues();
    for(var i=0; i<values.length; i++)
    {
      if(value == values[i][1]) {
        break;
      }
    }
    if (i >= values.length) {
      value = values[0][1];
      this.dropdownValues.setValue(value);
    }
  }*/
};

Blockly.Blocks.xblockly_xvoicebroadcast_stop = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XVoiceBroadcast', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XVoiceBroadcast.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_1)
        .appendField(dropdownInstances, "XVoiceBroadcast")
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_2);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_STOP);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xvoicebroadcast_isPlaying = {
    init: function () {
      function getMyVars() {
        return Blockly.getXBlocklyNameObjsByType('XVoiceBroadcast', [Blockly.Msg.MY_NULL, '']);
      }
      var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
      this.appendDummyInput()
          .appendField("")
          .appendField(new Blockly.FieldImage("../../media/xblockly/XVoiceBroadcast.png", 16, 16, "*"));
      this.appendDummyInput()
          .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_1)
          .appendField(dropdownInstances, "XVoiceBroadcast")
          .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_2);
      this.appendDummyInput()
          .appendField(Blockly.Msg.MY_XYGRVOICEBROADCAST_ISPLAYING);
      this.setInputsInline(true);
      this.setOutput(true, Boolean);
      //this.setPreviousStatement(true, null);
      //this.setNextStatement(true, null);
      this.setColour(xblockly_robotColor_display);
      this.setTooltip("");
      this.setHelpUrl("");
    }
  };

  Blockly.Blocks.xblockly_xpgklightshow_showColor = {
    init: function () {
      function getMyVars() {
        return Blockly.getXBlocklyNameObjsByType('XRGBLed', [Blockly.Msg.MY_NULL, '']);
      }
      var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
      var dropdownIndexs = new Blockly.FieldDropdown([
        [Blockly.Msg.MY_XRGBLED_INDEX_ALL, '0']
        , ['1', '1']
        , ['2', '2']
        , ['3', '3']
        , ['4', '4']]);
      this.appendDummyInput()
          .appendField("")
          .appendField(new Blockly.FieldImage("../../media/xblockly/XRGBLed.png", 16, 16, "*"));
      this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XRGBLED_1)
        .appendField(dropdownInstances, "XRGBLed")
        .appendField(Blockly.Msg.MY_XRGBLED_2);
      this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XRGBLED_SETCOLOR_INDEX_1)
        .appendField(dropdownIndexs, 'INDEX')
        .appendField(Blockly.Msg.MY_XRGBLED_SETCOLOR_INDEX_2);
      this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XRGBLED_SETCOLOR_VALUE_1);
      this.appendDummyInput("")
          .setAlign(Blockly.ALIGN_RIGHT)
          .appendField(new Blockly.FieldColour("#ff0000"), "COLOR")
        .appendField(Blockly.Msg.MY_XRGBLED_SETCOLOR_VALUE_2);
      this.setInputsInline(true);
      this.setPreviousStatement(true, null);
      this.setNextStatement(true, null);
      //this.setOutput(true, 'Number');
      this.setColour(xblockly_robotColor_display);
      this.setTooltip("");
      this.setHelpUrl("");
    }
  };
  
  Blockly.Blocks.xblockly_xpgklightshow_showRGB = {
    init: function () {
      function getMyVars() {
        return Blockly.getXBlocklyNameObjsByType('XRGBLed', [Blockly.Msg.MY_NULL, '']);
      }
      var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
      var dropdownIndexs = new Blockly.FieldDropdown([
        [Blockly.Msg.MY_XRGBLED_INDEX_ALL, '0']
        , ['1', '1']
        , ['2', '2']
        , ['3', '3']
        , ['4', '4']]);
      this.appendDummyInput()
          .appendField("")
          .appendField(new Blockly.FieldImage("../../media/xblockly/XRGBLed.png", 16, 16, "*"));
      this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XRGBLED_1)
        .appendField(dropdownInstances, "XRGBLed")
        .appendField(Blockly.Msg.MY_XRGBLED_2);
      this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XRGBLED_SETCOLOR_INDEX_1)
        .appendField(dropdownIndexs, 'INDEX')
        .appendField(Blockly.Msg.MY_XRGBLED_SETCOLOR_INDEX_2);
      this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XRGBLED_SHOWRGB_R_1);
      this.appendValueInput('R')
          .setCheck(Number);
      this.appendDummyInput()
          .appendField(Blockly.Msg.MY_XRGBLED_SHOWRGB_R_2);
      this.appendDummyInput()
          .appendField(Blockly.Msg.MY_XRGBLED_SHOWRGB_G_1);
      this.appendValueInput('G')
          .setCheck(Number);
      this.appendDummyInput()
          .appendField(Blockly.Msg.MY_XRGBLED_SHOWRGB_G_2);
      this.appendDummyInput()
          .appendField(Blockly.Msg.MY_XRGBLED_SHOWRGB_B_1);
      this.appendValueInput('B')
          .setCheck(Number);
      this.appendDummyInput()
          .appendField(Blockly.Msg.MY_XRGBLED_SHOWRGB_B_2);
      this.setInputsInline(true);
      this.setPreviousStatement(true, null);
      this.setNextStatement(true, null);
      //this.setOutput(true, 'Number');
      this.setColour(xblockly_robotColor_display);
      this.setTooltip("");
      this.setHelpUrl("");
    }
  };
  
  Blockly.Blocks.xblockly_xpgklightshow_clear = {
    init: function () {
      function getMyVars() {
        return Blockly.getXBlocklyNameObjsByType('XRGBLed', [Blockly.Msg.MY_NULL, '']);
      }
      var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
      var dropdownIndexs = new Blockly.FieldDropdown([
        [Blockly.Msg.MY_XRGBLED_INDEX_ALL, '0']
        , ['1', '1']
        , ['2', '2']
        , ['3', '3']
        , ['4', '4']]);
      this.appendDummyInput()
          .appendField("")
          .appendField(new Blockly.FieldImage("../../media/xblockly/XRGBLed.png", 16, 16, "*"));
      this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XRGBLED_1)
        .appendField(dropdownInstances, "XRGBLed")
        .appendField(Blockly.Msg.MY_XRGBLED_2);
      this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XRGBLED_CLEAR_INDEX_1)
        .appendField(dropdownIndexs, 'INDEX')
        .appendField(Blockly.Msg.MY_XRGBLED_CLEAR_INDEX_2);
      this.setInputsInline(true);
      this.setPreviousStatement(true, null);
      this.setNextStatement(true, null);
      //this.setOutput(true, 'Number');
      this.setColour(xblockly_robotColor_display);
      this.setTooltip("");
      this.setHelpUrl("");
    }
  };
  
Blockly.Blocks.xblockly_xpgkaudioplayer_playTone = {
  init: function() {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XBuzzer', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XBuzzer.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XBUZZER_1)
        .appendField(dropdownInstances, "XBuzzer")
        .appendField(Blockly.Msg.MY_XBUZZER_2);
    this.appendValueInput('FREQUENCY')
        .setCheck(Number)
        //.setAlign(Blockly.ALIGN_LEFT)
        .appendField(Blockly.Msg.MY_XBUZZER_PLAYTONE_FREQUENCY_1);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XBUZZER_PLAYTONE_FREQUENCY_2);
    this.appendValueInput('DURATION')
        .setCheck(Number)
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.Msg.MY_XBUZZER_PLAYTONE_DURATION_1);
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XBUZZER_PLAYTONE_DURATION_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true);
    this.setNextStatement(true);
    this.setHelpUrl(Blockly.Msg.MY_BUZZER_HELPURL);
    this.setColour(xblockly_robotColor_display);
  }
};

Blockly.Blocks.xblockly_xpgkaudioplayer_setNoteParameter = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XBuzzer', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XBuzzer.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUZZER_1)
      .appendField(dropdownInstances, "XBuzzer")
      .appendField(Blockly.Msg.MY_XBUZZER_2)
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUZZER_SETNOTEPARAMETER_BEATTIME_1)
    this.appendValueInput('BEATTIME')
      .setCheck(Number);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUZZER_SETNOTEPARAMETER_BEATTIME_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xpgkaudioplayer_playNote = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XBuzzer', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownNotes = new Blockly.FieldDropdown([
      ['DO', '1']
      , ['RE', '2']
      , ['ME', '3']
      , ['FA', '4']
      , ['SOL', '5']
      , ['LA', '6']
      , ['SI', '7']
      , ['0', '0']]);
    var dropdownScales = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XBUZZER_SCALE_LOW, '0']
      , [Blockly.Msg.MY_XBUZZER_SCALE_MEDIUM, '1']
      , [Blockly.Msg.MY_XBUZZER_SCALE_HIGH, '2']]);
    var dropdownTones = new Blockly.FieldDropdown([
      ['C', '0']
      , ['D', '1']
      , ['E', '2']
      , ['F', '3']
      , ['G', '4']
      , ['A', '5']
      , ['B', '6']]);
    var dropdownBeats = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XBUZZER_BEAT_1_8, '1']
      , [Blockly.Msg.MY_XBUZZER_BEAT_1_4, '2']
      , [Blockly.Msg.MY_XBUZZER_BEAT_1_2, '4']
      , [Blockly.Msg.MY_XBUZZER_BEAT_1, '8']
      , [Blockly.Msg.MY_XBUZZER_BEAT_2, '16']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XBuzzer.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUZZER_1)
      .appendField(dropdownInstances, "XBuzzer")
      .appendField(Blockly.Msg.MY_XBUZZER_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUZZER_PLAYNOTE_NOTE_1)
      .appendField(dropdownNotes, 'NOTE')
      .appendField(Blockly.Msg.MY_XBUZZER_PLAYNOTE_NOTE_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUZZER_PLAYNOTE_SCALE_1)
      .appendField(dropdownScales, 'SCALE')
      .appendField(Blockly.Msg.MY_XBUZZER_PLAYNOTE_SCALE_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUZZER_PLAYNOTE_TONE_1)
      .appendField(dropdownTones, 'TONE')
      .appendField(Blockly.Msg.MY_XBUZZER_PLAYNOTE_TONE_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUZZER_PLAYNOTE_BEAT_1)
      .appendField(dropdownBeats, 'BEAT')
      .appendField(Blockly.Msg.MY_XBUZZER_PLAYNOTE_BEAT_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xpgkaudioplayer_playMusic = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XBuzzer', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownValues = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XBUZZER_MUSIC_HAPPYBIRTHDAY, '1']
      , [Blockly.Msg.MY_XBUZZER_MUSIC_LITTLESTAR, '2']
      , [Blockly.Msg.MY_XBUZZER_MUSIC_SONGOFJOY, '3']
      , [Blockly.Msg.MY_XBUZZER_MUSIC_LITTLEAPPLE, '4']
      , [Blockly.Msg.MY_XBUZZER_MUSIC_GOTOSCHOOL, '5']]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XBuzzer.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUZZER_1)
      .appendField(dropdownInstances, "XBuzzer")
      .appendField(Blockly.Msg.MY_XBUZZER_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUZZER_PLAYMUSIC_VALUE_1)
      .appendField(dropdownValues, 'VALUE')
      .appendField(Blockly.Msg.MY_XBUZZER_PLAYMUSIC_VALUE_2);
    //this.appendDummyInput()
    //    .appendField(new Blockly.FieldCheckbox('FALSE'), 'REPEAT')
    //    .appendField(Blockly.Msg.MY_XBUZZER_PLAYMUSIC_REPEAT);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xpgkaudioplayer_playEffect = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XBuzzer', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var dropdownEffects = new Blockly.FieldDropdown([
      [Blockly.Msg.MY_XBUZZER_EFFECT_AMBULANCE, '1']
      , [Blockly.Msg.MY_XBUZZER_EFFECT_FIRE_ENGINE, '2']
      , [Blockly.Msg.MY_XBUZZER_EFFECT_POLICE_WAGON, '3']
      , [Blockly.Msg.MY_XBUZZER_EFFECT_CAR_WHISTLING, '4']
      ]);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XBuzzer.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUZZER_1)
      .appendField(dropdownInstances, "XBuzzer")
      .appendField(Blockly.Msg.MY_XBUZZER_2);
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XBUZZER_PLAYEFFECT_VALUE_1)
      .appendField(dropdownEffects, 'EFFECT')
      .appendField(Blockly.Msg.MY_XBUZZER_PLAYEFFECT_VALUE_2);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Number');
    this.setColour(xblockly_robotColor_display);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

/********************************************
Communicator - 通信模块
*********************************************/

Blockly.Blocks.xblockly_xirreceiver_presskey = {
  init: function () {
    var PRESSKEYS =
      [['0', '0'],
      ['1', '1'],
      ['2', '2'],
      ['3', '3'],
      ['4', '4'],
      ['5', '5'],
      ['6', '6'],
      ['7', '7'],
      ['8', '8'],
      ['9', '9'],
      ['A', '10'],
      ['B', '11'],
      ['C', '12'],
      ['D', '13'],
      ['E', '14'],
      ['F', '15'],
      ['↑', '16'],
      ['↓', '17'],
      ['←', '18'],
      ['→', '19'],
      ['OK', '20']];
    this.appendDummyInput()
      .appendField(new Blockly.FieldDropdown(PRESSKEYS), "PRESSKEY");
    this.setOutput(true, Number);
    this.setColour(xblockly_robotColor_communicator);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xirreceiver_enableLongPress = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XIRReceiver',[Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var PRESSKEYS = [['0', '0'],
    ['1', '1'],
    ['2', '2'],
    ['3', '3'],
    ['4', '4'],
    ['5', '5'],
    ['6', '6'],
    ['7', '7'],
    ['8', '8'],
    ['9', '9'],
    ['A', '10'],
    ['B', '11'],
    ['C', '12'],
    ['D', '13'],
    ['E', '14'],
    ['F', '15'],
    ['↑', '16'],
    ['↓', '17'],
    ['←', '18'],
    ['→', '19'],
    ['OK', '20']];
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIRReceiver.png", 16, 16, "*"));
    this.appendDummyInput()
        .appendField(Blockly.Msg.MY_XIRRECEIVER_1)
        .appendField(dropdownInstances, "XIRReceiver")
        .appendField(Blockly.Msg.MY_XIRRECEIVER_2)
        .appendField(Blockly.Msg.MY_XIRRECEIVER_ENABLELONGPRESS);
    // this.appendValueInput('VALUE')
    //   .setCheck(Number);
    this.appendDummyInput()
        .appendField(new Blockly.FieldDropdown(PRESSKEYS), "PRESSKEY");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, Blockly.Types.BOOLEAN.output);
    this.setColour(xblockly_robotColor_communicator);
    this.setTooltip("");
    this.setHelpUrl("");
  },
  getBlockType: function() {
    return Blockly.Types.BOOLEAN;
  }
};

Blockly.Blocks.xblockly_xirreceiver_available = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XIRReceiver',[Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIRReceiver.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRRECEIVER_1)
      .appendField(dropdownInstances, "XIRReceiver")
      .appendField(Blockly.Msg.MY_XIRRECEIVER_2)
      .appendField(Blockly.Msg.MY_XIRRECEIVER_AVAILABLE);
    this.setInputsInline(true);
    //this.setPreviousStatement(true, null);
    //this.setNextStatement(true, null);
    this.setOutput(true, Boolean);
    this.setColour(xblockly_robotColor_communicator);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xirreceiver_receiveNumber = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XIRReceiver',[Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    var PRESSKEYS = [['0', '0'],
    ['1', '1'],
    ['2', '2'],
    ['3', '3'],
    ['4', '4'],
    ['5', '5'],
    ['6', '6'],
    ['7', '7'],
    ['8', '8'],
    ['9', '9'],
    ['A', '10'],
    ['B', '11'],
    ['C', '12'],
    ['D', '13'],
    ['E', '14'],
    ['F', '15'],
    ['↑', '16'],
    ['↓', '17'],
    ['←', '18'],
    ['→', '19'],
    ['OK', '20']];
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIRReceiver.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRRECEIVER_1)
      .appendField(dropdownInstances, "XIRReceiver")
      .appendField(Blockly.Msg.MY_XIRRECEIVER_2)
      .appendField(Blockly.Msg.MY_XIRRECEIVER_RECEIVE);
    // this.appendValueInput('VALUE')
    //   .setCheck(Number);
    this.appendDummyInput()
      .appendField(new Blockly.FieldDropdown(PRESSKEYS), "PRESSKEY");
    this.setInputsInline(true);
    //this.setPreviousStatement(true, null);
    //this.setNextStatement(true, null);
    this.setOutput(true, Boolean);
    this.setColour(xblockly_robotColor_communicator);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

Blockly.Blocks.xblockly_xirreceiver_waitMessage = {
  init: function () {
    function getMyVars() {
      return Blockly.getXBlocklyNameObjsByType('XIRReceiver', [Blockly.Msg.MY_NULL, '']);
    }
    var dropdownInstances = new Blockly.FieldDropdown(getMyVars);
    this.appendDummyInput()
        .appendField("")
        .appendField(new Blockly.FieldImage("../../media/xblockly/XIRReceiver.png", 16, 16, "*"));
    this.appendDummyInput()
      .appendField(Blockly.Msg.MY_XIRRECEIVER_1)
      .appendField(dropdownInstances, "XIRReceiver")
      .appendField(Blockly.Msg.MY_XIRRECEIVER_2)
      .appendField(Blockly.Msg.MY_XIRRECEIVER_WAITMESSAGE);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    //this.setOutput(true, 'Boolean');
    this.setColour(xblockly_robotColor_communicator);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};

/********************************************
System - 系统模块
*********************************************/
