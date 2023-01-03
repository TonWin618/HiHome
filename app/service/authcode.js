'use strict'

const Service = require('egg').Service

class AuthcodeService extends Service{
    async createAuthcode(owner_id){
        try{
            const authInfo = await this.app.model.Authcode.findOne({
                where:{
                    [Op.and]: [{ owner_id: owner_id }, { active: "false" }]
                }
            })
            if(authInfo){
                return authInfo.authcode
            }else{
                var chars = '1234567890'
                var maxPos = chars.length
                var code = ''
                for (var i = 0; i < 6; i++) {
                    code += chars.charAt(Math.floor(Math.random() * maxPos))
                }
                this.app.model.Authcode.create({
                    owner_id: owner_id,
                    authcode: code,
                    active: "false"
                })
                return code
            }
        }catch(error){
            console.log(error)
            return false
        }
    }

    async getAuthcode(device_id){
        try{
            var {authcode} = await this.app.model.Authcode.findOne({
                where:{
                    [Op.and]: [{ device_id: device_id }, { active: "true" }]
                }
            })
            return authcode
        }catch(error){
            console.log(error)
            return false
        }
    }

    async setAuthcode(owner_id){
        try{
            await this.app.model.Authcode.update({
                active:"activing"
            },{
                where:{
                    [Op.and]: [{ owner_id: owner_id }, { active: "false" }]
                }
            })
        }catch(error){
            console.log(error)
            return false
        }
    }

    async isActiving(owner_id){
        try{
            await this.app.model.authcode.findOne({
                where:{
                    [Op.and]: [{ owner_id: owner_id }, { active: "activing" }]
                }
            })
            return true
        }catch(error){
            console.log(error)
            return false
        }
    }

    async getAuthcodeByUser(owner_id){
        try{
            var {authcode} = await this.app.model.Authcode.findOne({
                where:{
                    [Op.and]: [{ owner_id: owner_id }, { active: "false" }]
                }
            })
            return authcode
        }catch(error){
            console.log(error)
            return false
        }
    }

    async configDeviceId(owner_id, device_id){
        try{
            await this.app.model.Authcode.update({
                [Op.and]: [{ device_id: device_id }, { active: "true" }]
            },{
                where:{
                    [Op.and]: [{ owner_id: owner_id }, { active: "activing" }]
                }
            }
            )
        }catch{
            console.log(error)
            return false
        }
    }
}





module.exports = AuthcodeService;