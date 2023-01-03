module.exports = async function getIDbyToken(token){
    const id = await this.app.jwt.verify(token,this.app.config.jwt.secret).id;
    return id;
}