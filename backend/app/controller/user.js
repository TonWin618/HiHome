'use strict';

const Controller = require('egg').Controller;
class UserController extends Controller {
    //注册
    async create() {
        try {
            const {username,password} = this.ctx.request.body;
            if(username.length >= 4 && username.length <= 16){
                if(password.length>=6 && password.length<=16){
                    await this.ctx.service.user.createUser({username,password});
                    this.ctx.body = {
                        code: 20000,
                        message:true,
                    }
                }
            }
        }catch(error){
            this.ctx.body = {
                code: 30000,
                message:false
            }
        }
    }
    
    //登录
    async index() {
        try {
            const body = this.ctx.request.body
            const data = await this.ctx.service.user.login(body.username,body.password)
            if (data) {
                this.ctx.body = {
                    code: 20000,
                    message: true,
                    data: data,
                }
            } else {
                this.ctx.body = {
                    code: 40000,
                    message: false,
                }
            }
        } catch (error) {
            this.ctx.body = {
                code: 40000,
                message: false
            };
        }
    }
}

module.exports = UserController;
