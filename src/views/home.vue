<template>

  <div class="header">
    <el-row justify="center" align="middle">
      <el-col :span="6" >
        <el-button class="sider-button" @click="drawer=true" type="default" size="default" :plain=true>
          <el-icon size="20px" >
            <svg width="97" height="80" viewBox="0 0 97 80" fill="none" xmlns="http://www.w3.org/2000/svg">
              <path d="M0 0H97V16H0V0ZM0 32H97V48H0V32ZM0 64H97V80H0V64Z" fill="black"/>
            </svg>
          </el-icon>
        </el-button>
      </el-col>
      <el-col :span="12" >
        <h3 style="text-align:center">{{title}}</h3>
      </el-col>
      <el-col :span="6" >
        <h4 style="text-align:center">{{date.month}}月{{date.date}}日</h4>
      </el-col>
    </el-row>
  </div>

  <div class="back-hover" v-show="hoverVisible">
    <el-button class="back-button" type="primary" circle size="large" @click="backNormal">
        <el-icon size="30">
            <svg viewBox="0 0 1024 1024" xmlns="http://www.w3.org/2000/svg" data-v-029747aa="">
                <path fill="currentColor" d="M224 480h640a32 32 0 1 1 0 64H224a32 32 0 0 1 0-64z"></path>
                <path fill="currentColor" d="m237.248 512 265.408 265.344a32 32 0 0 1-45.312 45.312l-288-288a32 32 0 0 1 0-45.312l288-288a32 32 0 1 1 45.312 45.312L237.248 512z"></path>
            </svg>
      </el-icon>
    </el-button>
  </div>

  <div class="devices-page">
    <el-alert class="state-alert" :title="topAlert.title" :type="topAlert.type" effect="dark"  v-show="topAlert.visible" :closable="false"/>
    <div class="grid-container">
        <div class="grid-item" v-for="(device) in deviceList" :key="device.id" >
            <el-card :body-style="{padding: '0px'}" shadow="always" @click.native="clickEvent(device)">
                <div style="padding: 0px;">
                    <div style="text-align: right; padding-right: 6px;"> 
                        <svg width="10" height="10" viewBox="0 0 9 9" :fill="state_color" xmlns="http://www.w3.org/2000/svg">
                            <circle cx="4.5" cy="4.5" r="4.5"/>
                        </svg>
                    </div>
                    <div style="position: relative;">
                        <img :src="'/static/type_img/'+device.type_id+'.png'"  style="width:100%;height: 100%;" class="image">
                    </div>
                    <div style="position: relative;text-align: center;">
                        {{device.name}}
                    </div>
                </div>
            </el-card>
        </div>
    </div>
  </div>

  <el-drawer v-model="drawer"
    title="Hi,TonWin"
    direction="ltr"
    size="50%"
    :show-close=false
  >
    <template #header>
      <div>
        <el-image :src="require('../assets/logo.jpg')" style="width:80px;height:80px"></el-image>
      </div>
      <h3>Hi, {{username}}</h3>
    </template>

    <template #default>
      <el-menu
        default-active="0"
      >
      <el-divider content-position="center" class="item-divider"></el-divider>
        <el-menu-item index="1">
          <el-icon>
            <svg viewBox="0 0 1024 1024" xmlns="http://www.w3.org/2000/svg" data-v-029747aa="">
              <path fill="currentColor" d="M512 512a192 192 0 1 0 0-384 192 192 0 0 0 0 384zm0 64a256 256 0 1 1 0-512 256 256 0 0 1 0 512zm320 320v-96a96 96 0 0 0-96-96H288a96 96 0 0 0-96 96v96a32 32 0 1 1-64 0v-96a160 160 0 0 1 160-160h448a160 160 0 0 1 160 160v96a32 32 0 1 1-64 0z"></path>
            </svg>
          </el-icon>
          <span>个人信息</span>
        </el-menu-item>
        <el-menu-item index="2" @click="addDevice">
          <el-icon>
            <svg viewBox="0 0 1024 1024" xmlns="http://www.w3.org/2000/svg" data-v-029747aa="">
              <path fill="currentColor" d="M480 480V128a32 32 0 0 1 64 0v352h352a32 32 0 1 1 0 64H544v352a32 32 0 1 1-64 0V544H128a32 32 0 0 1 0-64h352z"></path>
            </svg>
          </el-icon>
          <span>添加设备</span>
        </el-menu-item>
        <el-menu-item index="3" @click="changeDevice">
          <el-icon>
            <svg viewBox="0 0 1024 1024" xmlns="http://www.w3.org/2000/svg" data-v-029747aa="">
              <path d="m199.04 672.64 193.984 112 224-387.968-193.92-112-224 388.032zm-23.872 60.16 32.896 148.288 144.896-45.696L175.168 732.8zM455.04 229.248l193.92 112 56.704-98.112-193.984-112-56.64 98.112zM104.32 708.8l384-665.024 304.768 175.936L409.152 884.8h.064l-248.448 78.336L104.32 708.8zm384 254.272v-64h448v64h-448z" fill="currentColor"></path>
            </svg>
          </el-icon>
          <span>修改设备</span>
        </el-menu-item>
        <el-menu-item index="4" @click="deleteDevice">
          <el-icon>
            <svg viewBox="0 0 1024 1024" xmlns="http://www.w3.org/2000/svg" data-v-029747aa="">
              <path fill="currentColor" d="M160 256H96a32 32 0 0 1 0-64h256V95.936a32 32 0 0 1 32-32h256a32 32 0 0 1 32 32V192h256a32 32 0 1 1 0 64h-64v672a32 32 0 0 1-32 32H192a32 32 0 0 1-32-32V256zm448-64v-64H416v64h192zM224 896h576V256H224v640zm192-128a32 32 0 0 1-32-32V416a32 32 0 0 1 64 0v320a32 32 0 0 1-32 32zm192 0a32 32 0 0 1-32-32V416a32 32 0 0 1 64 0v320a32 32 0 0 1-32 32z"></path>
            </svg></el-icon>
          <span>删除设备</span>
        </el-menu-item>
      </el-menu>
    </template>

    <template #footer>
      <div>
        <el-button class="logout-button" @click="logout" type="default" size="default" :plain=true >
          <el-icon size="30">
            <svg viewBox="0 0 1024 1024" xmlns="http://www.w3.org/2000/svg" data-v-029747aa="">
              <path fill="currentColor" d="M347.434667 181.632c0-18.176 13.098667-32.896 29.226666-32.896h382.293334c62.976 0 115.072 53.333333 115.072 120.704v526.592c0 67.413333-52.053333 120.704-115.072 120.704h-382.293334c-16.128 0-29.226667-14.72-29.226666-32.896 0-18.176 13.098667-32.938667 29.226666-32.938667h382.293334c31.829333 0 56.576-25.301333 56.576-54.869333V269.44c0-29.568-24.746667-54.869333-56.576-54.869333h-382.293334c-16.128 0-29.226667-14.762667-29.226666-32.938667z m-191.061334 333.696l3.2-3.669333 175.530667-175.530667A32.896 32.896 0 0 1 384.853333 378.965333l-3.2 3.712-119.296 119.338667h328.618667c9.941333 0 18.133333 12.16 19.541333 28.032l0.213334 4.864c0 16.554667-7.296 30.208-16.810667 32.554667l-2.944 0.384H262.314667l119.338666 119.338666a32.938667 32.938667 0 0 1 3.2 42.88l-3.2 3.669334a32.938667 32.938667 0 0 1-42.837333 3.2l-3.712-3.2-175.530667-175.530667a32.938667 32.938667 0 0 1-3.2-42.88z"></path>
            </svg>
          </el-icon>
          <span>注销</span>
        </el-button>
      </div>
    </template>
  </el-drawer>

  <AddDevice v-if="addPageVisible"  @refreshList="refreshList" ref="addPageRef"></AddDevice>
  <ControlPanel v-if="controlVisible" ref="controlPanelRef" :device="currentDevice"></ControlPanel>

</template>



<script setup>
  import { useRouter } from 'vue-router'
  import { reactive, ref, createApp, defineComponent } from 'vue';
  import { ElMessage,ElMessageBox  } from 'element-plus';
  import request  from '../utils/request.js';
  import AddDevice from '@/components/addDevice.vue';
  import ControlPanel from '@/components/controlPanel.vue';


  const router = useRouter();
  const title = ref("HOME");
  const username = ref('user');
  username.value = localStorage.getItem("username");
  const deviceList = ref([]);
  //状态
  const state = ref("normal");
  const state_color = ref("#2BF41A")//#BFC2BF
  //显示控制
  const drawer = ref(false);
  const addPageVisible = ref(false)
  const hoverVisible = ref(false)
  const controlVisible = ref(true)
  //顶部消息提示框
  const topAlert = reactive({
    visible:false,
    title:" ",
    type:"success"
  })
  //当前选中的设备
  const currentDevice = reactive({
    id:0,
    name:'',
    type_id:123,
  })

  const addPageRef = ref()
  const controlPanelRef = ref()

  const addDevice = () => {
    addPageVisible.value = true
    addPageRef.value.addPageMethod();
  }
  const controlPanel = () => {
    controlVisible.value = true;
    controlPanelRef.value.setVisible();
  }

  const refreshList = (val)=>{
    drawer.value = false;
    getDeviceList();
  }

  const clickEvent = (device) => {
    currentDevice.id = device.id;
    currentDevice.name = device.name;
    currentDevice.type_id = device.type_id;

    switch(state.value){
      case 'normal':
        controlPanel(currentDevice.id)
        break;
      case 'delete':
        destroyDevice(currentDevice.id)
        break;
      case 'change':
        updateDevice(currentDevice.id)
    }
  }
  

  const logout = () => {
    localStorage.removeItem("token");
    localStorage.removeItem("username");
    router.push('/login')
  }
  const backNormal = () => {
    state.value = "normal";
    topAlert.visible =false;
    hoverVisible.value = false;
  }
  const deleteDevice = () => {
    state.value = "delete";
    drawer.value = false;
    topAlert.type = "error";
    topAlert.title = "正在进行删除操作";
    topAlert.visible =true;
    hoverVisible.value = true;
  }
  const changeDevice = () => {
    state.value = 'change';
    drawer.value =false; 
    topAlert.type = "warning";
    topAlert.title = "正在进行修改操作";
    topAlert.visible =true;
    hoverVisible.value = true;
  }
  const getDeviceList = ()=>{
    request.get("/device").then((res) => {
      deviceList.value = res.data.data;
    })
  };
  getDeviceList();
  const destroyDevice = (device_id) => {
    ElMessageBox.confirm(
      '该操作将删除设备，确定要继续吗',
      '警告',
      {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning',
        center : true,
      }
    )
    .then(() => {
      request.delete(`/device/${device_id}`).then((res)=>{
        getDeviceList();
      })
      ElMessage({
        type: 'success',
        message: '删除成功',
      })
    })
    .catch(() => {

    })
  }

  const updateDevice = (device_id) => {
    ElMessageBox.prompt('请输入新的设备名称', '修改设备', {
    confirmButtonText: '确认',
    cancelButtonText: '取消',
    })
    .then(({ value }) => {
      request.put(`/device/${device_id}`,{name:value}).then((res)=>{
        getDeviceList();
      })
      ElMessage({
        type: 'success',
        message: '修改成功',
      })
    })
    .catch(() => {

    })
    
  }
  
  var date = reactive({
    month:'0',
    date:'0',
    day:'0'
  })
  var chineseWeek = ["日","一","二","三","四","五","六"]
  date = nowDate()
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
</script>

<style>
  .back-button{
    font-size: 20px;
  }
  .state-alert{
    bottom: 10px;
  }
  .header{ 
      position: fixed; 
      left: 0px; 
      top: 0px; 
      width: 100%; 
      height: 65px; 
      background-color: rgb(255, 255, 255); 
      box-shadow: 0px 1px 4px rgba(0,0,0,0.3);
      z-index: 50;
  }
  .back-hover{
    position: fixed;
    right: 20px;
    bottom:20px;
  }
  .sider-button{
    height: 54px;
    border: none;
  }
  .item-divider{
    width: 70%;
    margin-left: 20px;
  }
  .logout-button{
    width: 100%;
    justify-content: left;
    font-size: 16px;
    height: 40px;
    border: none;
    padding-left: 20px;
  }
  .devices-page{
    padding-top: 80px;
  }
  .control-panel{
    width: 400px;
    overflow: hidden;
  }

  .el-menu{
    border-right: 0px;
  }
  .el-menu-item{
    font-size: 16px;
  }
  .el-drawer{
    z-index:100;
    padding: 0 !important;
  }
  .el-drawer__header{
    margin-bottom: 0px ;
  }
  .el-drawer__body{
    padding:0 !important;
  }
  .el-drawer__footer{
    text-align:left;
    padding: 0px;
  }

  .grid-container {
    display: grid;
    grid-template-columns: repeat( auto-fit, 150px);
    row-gap: 30px;
    justify-items:center;
    justify-content: center;
  }
  .grid-item {
    height: 170px;
    Width: 120px;
    justify-content: center;
  }
  .el-card {
    width: 100%;
    height: 100%;
  }
  
</style>