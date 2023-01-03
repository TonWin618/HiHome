'use strict';

const Controller = require('egg').Controller;

class MqttController extends Controller {
    //MQTT连接鉴权
    async connectAuth(){
        try{
            const client = this.ctx.request.body
            if(client.type === "user"){
                var id = await this.app.jwt.verify(client.token,this.app.config.jwt.secret).id
                if(client.clientid === "user" + id){
                    this.ctx.body = {
                        result:"allow",
                        is_superuser :false
                    }
                }else{
                    throw false
                }
            }else if(client.type === "device"){
                var device_id = Number(client.clientid.substr(6))
                var code = await this.ctx.service.authcode.getAuthcode(device_id)
                if(client.token === code){
                    this.ctx.body  = {
                        result:"allow",
                        is_superuser :false
                    }
                }else{
                    throw false
                }
            }else if(client.type === "tryconnect"){
                var uid = Number(client.clientid)
                var code = client.token
                if(code === await this.service.authcode.getAuthcodeByUser(uid)){
                    await this.service.authcode.setAuthcode(uid)
                    this.ctx.body = {
                        result:"allow",
                        is_superuser: false
                    }
                }else{
                    throw false
                }
            }else{
                throw false
            }
        }catch(error){
            this.ctx.body = {
                result:"deny",
                is_superuser :false
            }
        }
    }
    //订阅发布鉴权
    async actionAuth(){
        try{
            const client = this.ctx.request.body
            console.log(client)
            if(client.type === "user"){
                if("user" + client.topic === client.clientid){
                    this.ctx.body = {
                        result: "allow"
                    }
                }
            }else if(client.type === "device"){
                var device_id = Number(client.clientid.substr(6))
                var uid = await this.ctx.service.device.getUserByDevice(device_id)
                if(client.topic === String(uid)){
                    this.ctx.body = {
                        result: "allow"
                    }
                }else{
                    throw false
                }
            }else if(client.clientid === "admin"){
                this.ctx.body = {
                    result: "allow"
                }
            }else{
                throw false
            }
        }catch(error){
            this.ctx.body = {
                result: "deny"
            }
        }
    }
};



module.exports = MqttController;
