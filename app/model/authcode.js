module.exports = app => {
    const {STRING} = app.Sequelize;

    const Authcode = app.model.define('authcode', {
        authcode: STRING,
        active: STRING,
    })

    Authcode.associate =  function(){
        app.model.Authcode.belongsTo(app.model.Device,{
            foreignKey:'device_id',
        })
        app.model.Authcode.belongsTo(app.model.User,{
            foreignKey:'owner_id',
        })
    }
    
    return Authcode;
}