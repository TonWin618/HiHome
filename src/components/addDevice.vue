<template>
  <el-dialog v-model="addDeviceVisible" title="选择设备类型" width="70%">
    <el-select class="type-select" v-model="deviceInfo.type_id" placeholder="未选择" size="large">
      <el-option  v-for="deviceType in typeList" :key="deviceType.id" :label="deviceType.name" :value="deviceType.id"/>
    </el-select>
    <template #footer>
      <span class="dialog-footer">
        <el-button @click="addDeviceVisible = false">取消</el-button>
        <el-button type="primary" @click="selectGateway">确认</el-button>
      </span>
    </template>
  </el-dialog>

  <el-dialog v-model="selectGatewayVisible" title="选择要绑定的网关" width="70%">
    <el-select class="type-select" v-model="deviceInfo.gateway_id" placeholder="未选择" size="large">
      <el-option v-for="gateway in gatewayList" :key="gateway.id" :label="gateway.name" :value="gateway.id"/>
    </el-select>
    <template #footer>
      <span class="dialog-footer">
        <el-button @click="selectGatewayVisible = false">取消</el-button>
        <el-button type="primary" @click="configDevice">确认</el-button>
      </span>
    </template>
  </el-dialog>

  <el-dialog v-model="configDeviceVisible" title="输入配置信息" width="70%">
    <span>
      蓝牙MAC地址：
      <el-input class="device-input" v-model="deviceInfo.bt_mac" placeholder="请输入" size="large"/>
    </span>
    <span>
      蓝牙连接密码：
      <el-input class="device-input" v-model="deviceInfo.bt_pin" placeholder="请输入" size="large"/>
    </span>
    <template #footer>
      <span class="dialog-footer">
        <el-button @click="configDeviceVisible = false">取消</el-button>
        <el-button type="primary" @click="createDevice">确认</el-button>
      </span>
    </template>
  </el-dialog>
</template>

<script setup>
  import { ref,reactive } from "vue";
  import request  from '../utils/request.js';
  import { ElMessage,ElMessageBox  } from 'element-plus';

  const emit = defineEmits(['refreshList']);
  const refresh = ()=>{
    emit("refreshList",'1');
  }

  const typeList = ref([])
  const gatewayList = ref([])

  const addDeviceVisible = ref(true);
  const selectGatewayVisible = ref(false)
  const configDeviceVisible = ref(false)
  
  const deviceInfo = reactive({
    type_id:null,
    gateway_id:null,
    bt_mac: null,
    bt_pin: null,
  })

  const addPageMethod = ()=>{
    addDeviceVisible.value = true;
  }

  const selectGateway = () => {
    getGatewayList();
    addDeviceVisible.value = false;
    selectGatewayVisible.value = true;
  }
  const configDevice = () => {
    selectGatewayVisible.value = false;
    configDeviceVisible.value = true;
  }

  const getTypeList = () => {
    request.get("/type").then((res) => {
      typeList.value = res.data.data
    })
  }
  getTypeList();

  const getGatewayList = () => {
    request.get("/device").then((res) => {
      gatewayList.value = res.data.data
    })
  }

  const createDevice = () => {
    request.post("/device",deviceInfo).then((res) => {
      if(res.data.message === true){
        ElMessage({
          message: '添加成功',
          type: 'success',
          grouping:true
        })
        configDeviceVisible.value = false;
        refresh();
      }else{
        ElMessage({
          message: '添加失败',
          type: 'error',
          grouping:true
        })
      }
    })
  }

  defineExpose({addPageMethod});
</script>

<style>
  .device-input{
    padding-bottom: 10px;
    padding-top: 1px;
  }
  .type-select{
    width: 100%;
  }
</style>