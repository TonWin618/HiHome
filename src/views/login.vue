<template>
    <el-row justify="center">
      <el-image :src="require('../assets/logo.jpg')" style="width:100px;height:100px"></el-image>
    </el-row>
  
    <el-row justify="center">
      <el-col :span="20">
        <el-input v-model="user.username" placeholder="请输入" size="large">
          <template #prepend>昵称</template>
        </el-input>
      </el-col>
    </el-row>
  
    <el-row justify="center">
      <el-col :span="20">
        <el-input v-model="user.password" type="password" placeholder="请输入" size="large" show-password>
          <template #prepend>密码</template>
        </el-input>
      </el-col>
    </el-row>
  
    <el-row>
      <el-col :span="10" :offset="12">
        <router-link to="/signup" class="superlink"> 没有账号，前去注册>> </router-link>
      </el-col>
    </el-row>
  
    <el-row justify="center">
      <el-col :span="12">
        <el-button @click="login" type="primary" size="large" style="width:100%;">登录</el-button>
      </el-col>
    </el-row>
</template>
  
<script setup>
  import { useRouter } from 'vue-router'
  import request from "../utils/request.js"
  import { reactive } from 'vue'
  import { ElMessage } from 'element-plus';
  const router = useRouter()
  const user = reactive({
    username:"",
    password:""
  });

  const login = ()=> {
    request.post("/login",{username:user.username,password:user.password}).then((res)=>{
      if(res.data.code === 20000){
        localStorage.setItem("token",res.data.data.token);
        localStorage.setItem("id",res.data.data.id);
        localStorage.setItem("username",user.username);
        ElMessage({
          message: '登陆成功',
          type: 'success',
          grouping:true
        })
        router.push('/');
      }else{
        ElMessage({
          message: '账号或密码错误',
          type: 'error',
          grouping:true
        })
      }
    })
  };
</script>

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
  