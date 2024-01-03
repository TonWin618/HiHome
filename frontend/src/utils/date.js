var chineseWeek = ["日","一","二","三","四","五","六"]

function nowDate() {
var now = new Date()
    var day = chineseWeek[now.getDay()]; //星期
    var month = now.getMonth() + 1; //月份
    var date = now.getDate(); //天数
    return ({
        month:month,
        date:date,
        day:day,
    })
};
export default nowDate