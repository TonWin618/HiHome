/* eslint valid-jsdoc: "off" */

'use strict';

/**
 * @param {Egg.EggAppInfo} appInfo app info
 */
module.exports = appInfo => {
  /**
   * built-in config
   * @type {Egg.EggAppConfig}
   **/
  const config = exports = {};

  // use for cookie sign key, should change to your own and keep security
  config.keys = appInfo.name + '_1664249406805_3406';

  // add your middleware config here
  config.middleware = [];

  // add your user config here
  const userConfig = {
    // myAppName: 'egg',
  };

  config.cors={
    origin:"*", //"*"代表所有的跨域请求
    credentials: true, // 允许跨域请求携带cookies
    allowMethods: 'GET,HEAD,PUT,POST,DELETE,PATCH'
  };

  config.jwt = {
    sercet:"hizngj"
  };

  config.sequelize = {
    dialect: 'mysql',
    database: 'hihome',
    host: 'localhost',
    port: 3306,
    username: 'root',
    password: '123456',
    timezone: '+08:00',
  };

  config.security = {
    csrf: {
        enable: false, // 前后端分离，post请求不方便携带_csrf
    },
    domainWhiteList: [
        '*',
    ], //配置白名单
  };

  return {
    ...config,
    ...userConfig,
  };
};
