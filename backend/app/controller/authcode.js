'use strict';

const Controller = require('egg').Controller

class AuthcodeController extends Controller {
    //更新设备验证码，如果没有就创建
    async index() {
        try{
            const token = this.ctx.request.header.token
            const id = this.app.jwt.verify(token,this.app.config.jwt.secret).id
            var authcode = await this.service.authcode.createAuthcode(id)
            this.ctx.body = {
                code:20000,
                message: true,
                data:{
                    authcode:authcode
                }
            }
        }catch(error){
            this.ctx.body = {
                code:30000,
                message: false,
            }
        }
    }

    async create(){
        try{
            const token = this.ctx.request.header.token
            const id = this.app.jwt.verify(token,this.app.config.jwt.secret).id
            const type_id = this.ctx.request.body.type_id
            if(await this.service.authcode.isActiving(id) === true){
                const device_id = await this.service.device.addDevice(id,type_id)
                this.ctx.body = {
                    code:20000,
                    message: true,
                    data:{
                        device_id:device_id
                    }
                }
            }else{
                throw false
            }
        }catch(error){
            this.ctx.body = {
                code:30000,
                message: false,
            }
        }
    }

    async update(){
        try{
            const token = this.ctx.request.header.token
            const id = this.app.jwt.verify(token,this.app.config.jwt.secret).id
            const device_id = this.ctx.request.body.device_id
            await this.service.authcode.configDeviceId(id, device_id)
            this.ctx.body = {
                code:20000,
                message: true,
            }
        }catch(error){
            this.ctx.body = {
                code:30000,
                message: false,
            }
        }
    }
}
module.exports = AuthcodeController;