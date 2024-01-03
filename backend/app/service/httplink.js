'use strict'

const Service = require('egg').Service

class HttplinkService extends Service{
    async createHttplink(device_id, httplink){
        try{
            this.app.model.Httplink.upsert({
                id:device_id,
                Httplink:httplink,
            },
            {
                where:{
                    id:device_id
                }
            }
            )
            return code
        }catch(error){
            console.log(error)
            return false
        }
    }

    async getHttplink(device_id){
        try{
            var {httplink} = await this.app.model.Httplink.findOne({
                where:{
                    id: device_id,
                }
            })
            return httplink
        }catch(error){
            console.log(error)
            return false
        }
    }
}

module.exports = HttplinkService;