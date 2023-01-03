'use strict';

const Service = require('egg').Service
var md5 = require('md5-node')

class UserService extends Service {
    //账号添加
    async createUser({username,password}) {
        try {
            if(await this.app.model.User.findOne({
                where:{
                    username : username
                }
            })===null){
                const user = {
                    username: username,
                    password: md5(password),
                }
                const theUser = await this.app.model.User.create(user)
                return true
            }else{
                return false
            }
        } catch (error) {
            return false
        }
    }

    async deleteUser({}){
        try{
            await this.app.model.User.destroy({
                where:{
                    id
                }
            })
            return true
        }catch(error){
            return false
        }
    }

    async updateUser(id,{username,password}){
        try{
            await this.app.model.User.update({
                username,
                password,
            },{
                where:{
                    id
                }
            })
            return true
        }catch(error){
            return false
        }
    }

    async getUserList(){
        try{
            const userList = await this.app.model.User.findAll();
            return userList;
        }catch(error){
            console.log(error)
            return false
        }
    }

    async login(username,password) {
        try {
            let passwordMd5 = md5(password)
            const user = await this.app.model.User.findOne({
                where: {
                    username:username
                }
            })
            console.log(user.dataValues.password)
            if(user){
                let psd = user.dataValues.password
                let usr = user.dataValues.username
                let uid = user.dataValues.id
                if (username === usr && passwordMd5 === psd) {
                    const token = this.app.jwt.sign({
                        id: uid
                    }, this.app.config.jwt.secret);
                    return {
                        token: token,
                        id: uid
                    }

                }else{
                    return false
                }
            }else {
                return false
            }
        } catch (error) {
            return false
        }
    }
}

module.exports = UserService;