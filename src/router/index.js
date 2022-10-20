import { createRouter,createWebHashHistory } from "vue-router";
const Login = ()=>import('../views/login.vue')
const Signup = () => import('../views/signup.vue')
const Home = () => import('../views/home.vue')
const Test = () => import('../components/controlPanel.vue')

const routes = [
    {
        path: '/',
        name: '主页',
        meta: {title:'首页 - Hi智能管家'},
        component: Home
    },
    {
        path: '/login',
        name: '登录 - Hi智能管家',
        component: Login
    },
    {
        path: '/signup',
        name: '注册 - Hi智能管家',
        component: Signup
    },
    {
        path:'/test',
        name:'测试用例',
        component:Test
    }
]

export const router = createRouter({
    history: createWebHashHistory(process.env.BASE_URL),
    routes: routes
  })
  
  export default router