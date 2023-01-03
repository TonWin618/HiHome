module.exports = app => {
    const {INTEGER,STRING} = app.Sequelize;

    const Device = app.model.define('device', {
        id: {type: INTEGER, primaryKey:true , autoIncrement:true},
        name:STRING
    })

    Device.associate =  function(){
        app.model.Device.belongsTo(app.model.User,{
            foreignKey:'owner_id',
        })
        app.model.Device.belongsTo(app.model.Type,{
            foreignKey:'type_id',
        })
    }
    return Device;
}