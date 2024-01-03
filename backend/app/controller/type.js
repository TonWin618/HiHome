'use strict'

const Controller = require('egg').Controller

class TypeController extends Controller{
    //获取设备类型列表
    async index(){
        try{
            const typeList = await this.ctx.service.type.getTypeList();
            this.ctx.body = {
                code:20000,
                message: true,
                data: typeList
            }
        }catch(error){
            this.ctx.body = {
                code:30000,
                message: false,
            }
        }
    }
    //添加一个设备类型
    async create(){
        try{
            const { name,add } = this.ctx.request.body
            await this.ctx.service.type.createType(name,add);
            this.ctx.body = {
                code:20000,
                message: true,
            }
        }catch(error){
            this.ctx.body = {
                code: 30000,
                message: false
            }
        }
    }
    //删除一个设备类型
    async destroy(){
        try{
            const id = this.ctx.params.id;
            await this.ctx.service.type.deleteType(id);
            this.ctx.body = {
                code: 20000,
                message: true
            }
        }catch(error){
            this.ctx.body = {
                code: 30000,
                message: false
            }
        }
    }
    //修改设备类型信息
    async update(){
        try{
            const id = this.ctx.params.id;
            const {name,add} = this.ctx.request.body;
            await this.ctx.service.type.updateType(id,name,add);
            this.ctx.body = {
                code: 20000,
                message: true
            }
        }catch(error){
            this.ctx.body = {
                code: 30000,
                message: false
            }
        }
    }
}

module.exports = TypeController