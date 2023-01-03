'use strict';

const Controller = require('egg').Controller

class HttplinkController extends Controller {
    //更新一个http设备信息，如果没有就创建
    async create() {
        try{
            const token = this.ctx.request.header.token
            const type_id = this.ctx.request.body.type_id
            const httplink = this.ctx.body.httplink
            const id = this.app.jwt.verify(token,this.app.config.jwt.secret).id
            const device_id = await this.service.device.addDevice(id, type_id)
            await this.service.httplink.createHttplink(device_id,httplink)
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
module.exports = HttplinkController;