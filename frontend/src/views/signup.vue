<template>
    <el-row justify="center">
      <el-image :src="require('../assets/logo.jpg')" style="width:100px;height:100px"></el-image>
    </el-row>
  
    <el-row justify="center">
      <el-col :span="20">
        <el-input v-model="user.name" placeholder="请输入" size="large">
          <template #prepend>用户名称</template>
        </el-input>
      </el-col>
    </el-row>
  
    <el-row justify="center">
      <el-col :span="20">
        <el-input v-model="user.password1" type="password" placeholder="请输入" size="large">
          <template #prepend>登录密码</template>
        </el-input>
      </el-col>
    </el-row>

    <el-row justify="center">
      <el-col :span="20">
        <el-input v-model="user.password2" type="password" placeholder="请输入" size="large">
          <template #prepend>确认密码</template>
        </el-input>
      </el-col>
    </el-row>
  
    <el-row>
      <el-col :span="10" :offset="12">
        <router-link to="/login" class="superlink"> 已有账号，直接登录>> </router-link>
      </el-col>
    </el-row>
  
    <el-row justify="center">
      <el-col :span="12">
        <el-button @click="signup" type="primary" size="large" style="width:100%;">注册</el-button>
      </el-col>
    </el-row>
  </template>
  
  <script setup>
    import { useRouter } from 'vue-router'
    import request from "../utils/request"
    import { reactive } from 'vue'
    import { ElMessage } from "element-plus";

    const router = useRouter()
    const user = reactive({
      id:0,
      name:"",
      password1:"",
      password2:""
    });
  
    const signup = ()=> {
      if(user.name.length >= 4 && user.name.length <= 16){
        if(user.password1.length>=6 && user.password1.length<=16){
          if(user.password1 === user.password2){
            request.post("/signup",{
              username:user.name,
              password:user.password1
            }).then((res)=>{
              if(res.data.code === 20000){
                router.push('/login');
              }else if(res.data.code === 30000){
                ElMessage({
                  message: '用户名重复',
                  type: 'error',
                  grouping:true
                })
              }else{
                ElMessage({
                  message: '注册失败',
                  type: 'error',
                  grouping:true
                })
              }
            })
          }else{
            ElMessage({
              message: '两次输入的密码不一致',
              type: 'error',
              grouping:true
            })
          }
        }else{
          ElMessage({
          message: '密码长度限制在6~16个字符',
          type: 'error',
          grouping:true
        })
        }
      }else{
        ElMessage({
          message: '用户名长度限制在4~16个字符',
          type: 'error',
          grouping:true
        })
      }
    }
  </script>
  
  <!-- Add "scoped" attribute to limit CSS to this component only -->
  <style scoped>
    .el-row{
      margin-bottom: 12px;
    }
    .el-input{
      font-size: 16px;
    }
    .el-button{
        font-size: 16px;
    }
    .superlink{
      font-size: 14px;
      text-decoration: none;
      color: var(--el-color-primary);
    }
  </style>