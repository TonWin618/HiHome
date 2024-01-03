'use strict';

const Controller = require('egg').Controller;

class HomeController extends Controller {
  async index() {
    const ctx = this.ctx;
    ctx.body = 'Hi智能管家'
  };
}
module.exports = HomeController;
