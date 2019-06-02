cochat HTTP socketIo 同步模拟



//登录结果 userInfo
{
	"CONF_VARS": {
		"@C_CC_OPEN_MAIL_OPEN_TYPES@": "doc,docx,xls,xlsx,pdf,ppt,txt,html,htm,jpg,gif,png,jpeg",
		"@C_OP_COMM_ADDRESS_OPEN_OBJ@": "{'DEPTS':'ruaho_leader','ROLES':'RGSLD','USERS':'admin'}",
		"@C_SY_ASYNC_LOG_HANDLER_INTERVAL@": "120000",
		"@C_MAIL_MESSAGE_USER_NAME@": "test1@staff.ruaho.com",
		"@C_SY_LOGS_PATH@": "",
		"@C_SY_WF_NODE_SIZE@": "100,40",
		"@C_SY_EMAIL_ADDR@": "mailto:#USER_CODE#@staff.zotn.com",
		"@C_SY_COMM_SOCKET_SERV_V1.0@": "http:\/\/cochat.cn:9091",
		"@C_CO_REDIS_SERVER@": "localhost",
		"@C_SY_COMM_BATCH_SAVE_LOG_MAX_SIZE@": "500",
		"@C_MSG_SENDER_IMPL_PREFIX_EMAIL@": "com.rh.core.comm.msg.MailMsgSender",
		"@C_SY_COMM_NEWS_STATIC_FILE_ROOT@": "smb:\/\/cochat:cochat@172.16.0.5\/file\/cms",
		"@C_SY_COCHAT_CONFIG@": "{\"open\":true,\"address\":\"http:\/\/www.cochat.cn\/www\"}",
		"@C_SY_PLUG_REPORT_FR@": "http:\/\/localhost:9090\/report\/ReportServer",
		"@C_SY_WF_BTN_GROUP_RENDER@": "true",
		"@C_SY_TAB_MAX@": "10",
		"@C_CO_MONGO_SERVER@": "localhost",
		"@C_CM_MIND_SORT_TYPE@": "TYPE",
		"@C_SY_WF_NEXT_STEP@": "",
		"@C_SY_TODO_NOTIFY_EXPAND_CLASS@": "com.rh.cochat.open.shenpi.TodoSend",
		"@C_SY_COMM_REMIND_TIME_VALID@": "30",
		"@C_DEVICE_TYPE@": "DESKTOP",
		"@C_MOBILE_SERVER@": "false",
		"@C_SY_HOME_CONFIG@": "",
		"@C_MAIL_MESSAGE_PASSWORD@": "ruaho1234",
		"@C_SY_PLUG_WEBIM_SERVER@": "http:\/\/172.16.0.4:7070\/http-bind\/",
		"@C_SY_STYLE_DEF@": "",
		"@C_SY_PORTAL_ICON@": "\/sy\/comm\/page\/img\/logo_ruaho.gif",
		"@C_SY_HOMEMENU_LOC@": "2",
		"@C_OP_COMM_ADDRESS_SECURED_CLASS@": "com.rh.core.comm.txl.DefTxlSecurer",
		"@C_CO_MONGO_USERNAME@": "root",
		"@C_审批APP@": "",
		"@C_MAIL_MESSAGE_IF_AUTH@": "true",
		"@C_SY_WBIM_FLAG@": "false",
		"@C_OP_COMM_ADDRESS_CTR_INFO@": "USER_MOBILE: ",
		"@C_DOCVIEW_ENABLE@": "false",
		"@C_CC_USER_FIRENDS_STRATEGY@": "dept",
		"@C_SY_COMM_TRANS_SERV@": "http:\/\/cochat.cn:8093\/api\/html\/trans",
		"@C_SY_ORG_USER_DEFAULT_IMG@": "07zeB-fqx38ELGprH0ay_M.png",
		"@C_SY_DESK_MSG_INTERVAL@": "300000",
		"@C_SY_ORG_LOGIN_MODULE_NAME@": "custom",
		"@C_SY_HUB_IM@": "com.rh.core.plug.im.ImRtx",
		"@C_SY_MB_LINK@": "true",
		"@C_MAIL_MESSAGE_SENDER@": "测试<test1@staff.ruaho.com>",
		"@C_SY_EXP_NUM@": "5000",
		"@C_SY_ASYNC_LOG_HANDLER_MAX_MSG_COUNT@": "300",
		"@C_SY_BANNER_SEARCH@": "false",
		"@C_CC_ORG_ADDRESS_EXPAND_CONF@": "com.rh.cochat.serv.OrgAddressExpandRHServ\n",
		"@C_SY_BANNER_CONFIG@": "{'banner':'\/sy\/comm\/page\/img\/head_logo.jpg','bannerBack':'\/sy\/comm\/page\/img\/head_bg.gif'}\r\n",
		"@C_SY_COMM_WORK_TIME@": "08:30:00,11:30:00,13:00:00,18:00:00",
		"@C_CO_REDIS_PASSWORD@": "",
		"@C_SY_PLUG_SEARCH_FILE_REDIRECT_SERVER@": "http:\/\/115.28.45.203:1897\/file\/",
		"@C_SY_COMM_SOCKET_SERV@": "http:\/\/cochat.cn:9092",
		"@C_SY_WF_DIRECT_SEND@": "true",
		"@C_CC_DESKTOP_MAIN_MENU_THEME@": "1",
		"@C_SY_COMM_BATCH_SAVE_LOG_INTERVAL@": "300",
		"@C_CO_MONGO_PASSWORD@": "",
		"@C_SY_DEV_USERS@": "admin,superadmin,000803837",
		"@C_SY_COMM_REMIND_TIME_RANGE@": "5",
		"@C_SY_WF_BACK_NODE_NAME@": "",
		"@C_SY_PLUG_REPORT_CHART@": "SY_COMM_INFO.chart.do",
		"@C_SY_PLUG_REPORT_XDOC@": "http:\/\/localhost:8080\/xdoc",
		"@C_MSG_SENDER_IMPL_PREFIX_TODO@": "com.rh.core.comm.msg.TodoMsgSender",
		"@C_SY_ORG_LOGIN_MODULE_CLASS@": "com.rh.cochat.serv.login.CochatLoginModule",
		"@C_MAIL_MESSAGE_HOST@": "smtp.exmail.qq.com",
		"@C_SY_BANNER_ICON@": "{\"cmpy\":{\"url\":\"SY_COMM_TEMPL.show.do?pkCode=1-QuWdguJ0L8f8tG8YbHMy&model=view\",\"name\":\"公司门户\",\"menuId\":\"\"},\r\n\"dept\":{\"url\":\"SY_COMM_TEMPL.show.do?pkCode=1PL1etY999C8jjte_iE68G&model=view\",\"name\":\"部门门户\",\"menuId\":\"\"},\r\n\"user\":{\"url\":\"SY_COMM_TEMPL.show.do?pkCode=29PnOt0Bl8eauAM9M74cVT&model=view\",\"name\":\"个人门户\",\"menuId\":\"\"}}"
	},
	"_PK_": "abcKdBQpcBrrJ4Aj4qprw",
	"MODIFY_PASSWORD": "",
	"USER_CODE": "0M4fxUb1d10H5HBbpSKoCZ",
	"USER_TOKEN": "caf2ea9cec1f283c8588340a3583d756",
	"_TIME_": "0.013",
	"_MSG_": "OK,",
	"HASBIND": "CHENPENGHUI@RUAHO.COM",
	"ORG_VARS": {
		"@ADMIN_GROUP_CODES@": "''",
		"@USER_SEX@": "1",
		"@ODEPT_SRC_TYPE2@": "",
		"@LEAD_CODES@": "''",
		"@S_MTIME@": "2018-06-12 10:49:01:905",
		"@ODEPT_LEVEL@": "2",
		"@ACCOUNT_STATE@": "2",
		"@CMPY_CODE@": "ruaho",
		"@ROLE_CODES@": "'RPUB','RPUB2'",
		"@CMPY_PT@": "2uyWMoDQB0LX2cL6lOQxEo",
		"@TDEPT_NAME@": "南京研发中心",
		"@USER_CMLE_DEG@": "0",
		"@DEPT_SRC_TYPE2@": "",
		"@TDEPT_CODE@": "2JsTkW1yIRfjXk20jBM6olN",
		"@USER_BIRTHDAY@": "",
		"@USER_IMG@": "\/file\/ICON_1ksJMkeLx2T9LDIcGAnGJPt.png?t=2018-06-12 10:49:01:905",
		"@USER_MOBILE@": "18408249138",
		"@USER_EMAIL@": "chenpenghui@ruaho.com",
		"@ODEPT_SRC_TYPE1@": "",
		"@USER_IDCARD@": "",
		"@ODEPT_NAME_M@": "'南京研发中心'",
		"@USER_WORK_NUM@": "18408249138",
		"@GROUP_CODES@": "''",
		"@TDEPT_SRC_TYPE2@": "",
		"@ODEPT_CODE_PATH@": "ruaho^2JsTkW1yIRfjXk20jBM6olN^",
		"@ODEPT_FULL_NAME@": "软虹南京研发中心",
		"@LOGIN_NAME@": "18408249138",
		"@CMPY_NAME@": "软虹科技",
		"@USER_ROOM@": "",
		"@JIAN_CODES@": "",
		"@TDEPT_CODE_M@": "'2JsTkW1yIRfjXk20jBM6olN'",
		"@DEPT_CODE@": "2JsTkW1yIRfjXk20jBM6olN",
		"@CMPY_FULLNAME@": "软虹科技",
		"@TDEPT_NAME_M@": "'南京研发中心'",
		"@DEPT_NAME_M@": "'南京研发中心'",
		"@DEPT_CODES@": "'2JsTkW1yIRfjXk20jBM6olN',''",
		"@ODEPT_CODE_M@": "'2JsTkW1yIRfjXk20jBM6olN'",
		"@TDEPT_SRC_TYPE1@": "",
		"@TDEPT_PT@": "",
		"@SUB_CODES@": "''",
		"@DEPT_NAME@": "南京研发中心",
		"@DEPT_CODE_M@": "'2JsTkW1yIRfjXk20jBM6olN'",
		"@USER_CODE@": "0M4fxUb1d10H5HBbpSKoCZ",
		"@USER_POST@": "工程师",
		"@AGT_FLAG@": "2",
		"@USER_NAME@": "陈鹏辉",
		"@ODEPT_PT@": "",
		"@DEPT_LINE@": "",
		"@ODEPT_CODE@": "2JsTkW1yIRfjXk20jBM6olN",
		"@USER_PT@": "SY_USER_CENTER",
		"@OFFICE_PHONE@": "",
		"@DEPT_SRC_TYPE1@": "",
		"@ODEPT_NAME@": "南京研发中心",
		"@urlPath@": "",
		"@USER_IMG_SRC@": "1ksJMkeLx2T9LDIcGAnGJPt.png",
		"@ODEPT_PCODE@": "ruaho"
	}
}







//socket 认证参数
CurrentUser.getConfig()
this.getServer(), this.getToken(), this.getUuid()
    config = {};
    config.server = results[0];
    var url = results[0] + "/";
    if (url.toLowerCase().indexOf('http://') < 0) {
        url = 'http://' + url;
    }
    config.url = url;
    config.uuid = results[2];
    config.header = {"X-DEVICE-NAME": results[2]};
    if (results[1]) {
        config.header["X-XSRF-TOKEN"] = results[1];
    }
                                

                USER_ORG                USER_SERVER:'http://122.20.61.8:9080/' USER_TOKEN UUID
CurrentUser.getUserInfo(), CurrentUser.getConfig()
                                
0: 
1:
header:{X-DEVICE-NAME: "@3b7904bb-20ba-7820-fab3-0bb28b68c4fe", X-XSRF-TOKEN: "5855fb3a4553165e1cfcae13eecedb5b"}
server:"http://122.20.61.8:9080/"
url:"http://122.20.61.8:9080//"
uuid:"@3b7904bb-20ba-7820-fab3-0bb28b68c4fe"
__proto__:Object


//socket连接操作

var config = {
    transports:['websocket', 'polling'], // websocket优先
    timeout:30 * 1000, // 超时时间
    forceNew: true,
    reconnection : false
};


server = USER_PARAM[@C_SY_COMM_SOCKET_SERV_V1.0@] :http://cochat.cn:9091   ！USER_PARAM
socket = io(server, config);        //#######################
socket.on('connect', function () { // 登录成功返回socket
var token = params[1].header["X-XSRF-TOKEN"];    
   
socket.emit('loginv17', {
    userName: params[0].USER_CODE,
    displayName: params[0].USER_NAME,
    odept: params[0].ODEPT_CODE,
    token: token,
    uuid: params[1].uuid,
    version: LocalStore.get(params[2]['USER_CODE'] + '_LAST_MSG')
}, function (offlineDatas) {
    if (offlineDatas) { // 登录成功后执行
        console.info("登录回调.loginv17.callback:!!!!");
        console.info(offlineDatas)
        var allDatas = offlineDatas['data'];
        logined = true;
        Connection.setOnline();

        // 广播成功消息
        $rootScope.$broadcast("socket:login");
}}
                            
socket.on('disconnect', function () )
socket.on('error', function () )
socket.on('connect_error', function () )
socket.on('connect_timeout', function () )
socket.on('connecting', function () )
socket.on('reconnecting', function () )
socket.on('ping', function () )
socket.on('pong', function () )
socket.on('event', function () )
socket.on('message', function () )


                            

                            


//单聊自己发的消息
({
	u'body': u'222222',
	u'category': u'',
	u'from': {
		u'nickName': u'\u9648\u9e4f\u8f89',
		u'type': u'USER',
		u'id': u'0M4fxUb1d10H5HBbpSKoCZ',
		u'fullId': u'u__0M4fxUb1d10H5HBbpSKoCZ'
	},
	u'version': u'0',
	u'notification': None,
	u'clientId': u'2ZNjD9Yud7XG3N2j7KfYLM',
	u'to': {
		u'nickName': u'\u8bb8\u6b22',
		u'type': u'USER',
		u'id': u'21JnEtnsdaY8e3mVOJ3mgdlA',
		u'fullId': u'u__21JnEtnsdaY8e3mVOJ3mgdlA'
	},
	u'responseTimeMillis': 1530698049248,
	u'contact': {
		u'nickName': u'\u8bb8\u6b22',
		u'type': u'USER',
		u'id': u'21JnEtnsdaY8e3mVOJ3mgdlA',
		u'fullId': u'u__21JnEtnsdaY8e3mVOJ3mgdlA'
	},
	u'at': u'',
	u'time': u'2018-07-0417: 54: 09: 248',
	u'bodyType': u'text',
	u'timeMillis': 1530698049248,
	u'id': u'm_5b3c99410cf2f54802256721',
	u'datas': {
		u'unreadCount': u'1'
	}
},
<function<lambda>at0x7fc33cb7c578>)










//websocket 浏览器访问参数
ws://cochat.cn:9091/socket.io/?EIO=3&transport=websocket

Accept-Encoding:gzip, deflate
Accept-Language:zh-CN,zh;q=0.9
Cache-Control:no-cache
Connection:Upgrade
DNT:1
Host:cochat.cn:9091
Origin:http://picc.cochat.cn
Pragma:no-cache
Sec-WebSocket-Extensions:permessage-deflate; client_max_window_bits
Sec-WebSocket-Key:1Ibe2QLYCW6+qNSIsL31gw==
Sec-WebSocket-Version:13
Upgrade:websocket
User-Agent:Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36
























