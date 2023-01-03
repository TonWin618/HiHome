'use strict'

const checktoken = require("./middleware/checktoken")

/**
 * @param {Egg.Application} app - egg application
 */
module.exports = app => {
  const { router, controller } = app

  router.get('/',controller.home.index)
  router.post('/login',controller.user.index)
  router.post('/signup',controller.user.create)

  router.resources('type','/type', checktoken(),controller.type)
  router.resources('device','/device', checktoken(),controller.device)

  router.post('/auth/connect', controller.mqtt.connectAuth)
  router.post('/auth/action', controller.mqtt.actionAuth)
  
  router.get('/auth/authcode', checktoken(), controller.authcode.index)
  router.post('auth/authcode',checktoken(), controller.authcode.create)
  router.put('auth/authcode', checktoken(), controller.authcode.update)

  router.post('/auth/httplink', checktoken(), controller.httplink.create)
  
  router.index
}
