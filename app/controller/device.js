'use strict'

const getIDbyToken = require('../utils/getIDbyToken');

const Controller = require('egg').Controller

class DeviceController extends Controller{
    //获取设备列表
    async index(){
        const {ctx,app} = this;
        try{
            const token = ctx.request.header.token
            const id = await app.jwt.verify(token,app.config.jwt.secret).id;
            const deviceList = await ctx.service.device.getDeviceList(id);
            this.ctx.body = {
                code:20000,
                message: true,
                data: deviceList
            }
        }catch(error){
            this.ctx.body = {
                code:30000,
                message: false,
            }
        }
    }
    //添加设备
    async create(){
        try{
            const token = this.ctx.request.header.token
            const id = await this.app.jwt.verify(token,this.app.config.jwt.secret).id;
            const type_id = this.ctx.request.body.type_id
            var device_id = await this.ctx.service.device.addDevice(id,type_id);
            this.ctx.body = {
                code:20000,
                message: true,
                data:{
                    device_id:device_id
                }
            }
        }catch(error){
            this.ctx.body = {
                code:30000,
                message: false,
            }
        }
    }
    //删除设备
    async destroy(){
        try{
            const token = this.ctx.request.header.token
            const id = await this.app.jwt.verify(token,this.app.config.jwt.secret).id;
            const device_id = this.ctx.params.id;
            await this.ctx.service.device.deleteDevice(device_id);
            this.ctx.body = {
                code: 20000,
                message: true
            }
        }catch(error){
            this.ctx.body = {
                code:30000,
                message: false,
            }
        }
    }
    //修改设备
    async update(){
        try{
            const token = this.ctx.request.header.token
            const id = await this.app.jwt.verify(token,this.app.config.jwt.secret).id;
            const device_id = this.ctx.params.id
            const body = this.ctx.request.body
            await this.ctx.service.device.updateDevice(id,device_id,body);
            this.ctx.body = {
                code: 20000,
                message: true
            }
        }catch(error){
            this.ctx.body = {
                code:30000,
                message: false,
            }
        }
    }
}

module.exports = DeviceController