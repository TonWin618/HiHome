'use strict';

const Service = require('egg').Service

class DeviceService extends Service{
    //获取设备列表
    async getDeviceList(owner_id){
        try{
            const deviceList = await this.app.model.Device.findAll({
                attributes: [this.app.Sequelize.col('type.add'),'id', 'name','type_id'],
                include:{
                    model:this.app.model.Type,
                    attributes:[]
                },
                where:{
                    owner_id:owner_id
                },
                raw:true
            })
            return deviceList
        }catch(error){
            console.log(error);
            return false
        }
    }

    //添加设备
    async addDevice(owner_id,type_id){
        try{
            const type = await this.app.model.Type.findByPk(type_id)
            const device = {
                name:type.name,
                type_id: type_id,
                owner_id : owner_id,
            }
            var newDevice = await this.app.model.Device.create(device);
            return newDevice.id;
        }catch(error){
            console.log(error);
            return false
        }
    }

    //删除设备
    async deleteDevice(device_id){
        try{
            await this.app.model.Device.destroy({
                where:{
                    id:device_id
                }
            });
            return true
        }catch(error){
            console.log(error)
            return false
        }
    }

    //修改设备名
    async updateDevice(id,device_id,body){
        try{
            await this.app.model.Device.update({
                name:body.name,
            },
            {
                where:{
                    id:device_id
                },
            })
            return true
        }catch(error){
            console.log(error)
            return false
        }
    }
    //查找该设备拥有者id
    async getUserByDevice(device_id){
        try{
            const device = await this.app.model.Device.findByPk(device_id)
            return device.owner_id
        }catch(error){
            console.log(error)
            return false
        }
    }
}

module.exports = DeviceService