module.exports = app => {
    const {STRING , INTEGER} = app.Sequelize;

    const Type = app.model.define('type', {
        id: {type: INTEGER, primaryKey:true , autoIncrement:true},
        name: STRING,
        add: STRING,
    })
    
    return Type;
}