'use strict';

const Service = require('egg').Service

class TypeService extends Service{
    async createType(name,add){
        try{
            const type = {
                name: name,
                add: add
            }
            await this.app.model.Type.create(type);
            return true;
        }catch(error){
            console.log(error);
            return false
        }
    }

    async getTypeList(){
        try{
            const typeList = await this.app.model.Type.findAll();
            return typeList;
        }catch(error){
            console.log(error);
            return false
        }
    }

    async deleteType(id){
        try{
            await this.app.model.Type.destroy({
                where:{
                    id
                }
            })
            return true
        }catch(error){
            return false
        }
    }

    async updateType(id,name,add){
        try{
            await this.app.model.Type.update({
                name,
                add,
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
}

module.exports = TypeService