module.exports = app => {
    const {STRING} = app.Sequelize;

    const Httplink = app.model.define('httplink', {
        httplink: STRING,
    })

    Httplink.associate =  function(){
        app.model.Authcode.belongsTo(app.model.Device,{
            foreignKey:'device_id',
        })
    }
    
    return Httplink;
}