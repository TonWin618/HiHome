<template>
  
  <el-dialog v-model="addDeviceVisible" title="选择设备类型" width="70%">
    <el-select class="type-select" v-model="selectedType.type_id" placeholder="未选择" size="large">
      <el-option  v-for="deviceType in typeList" :key="deviceType.id" :label="deviceType.name" :value="deviceType.id"/>
    </el-select>
    <template #footer>
      <span class="dialog-footer">
        <el-button @click="addDeviceVisible = false">取消</el-button>
        <el-button type="primary" @click="addDeviceByType">确认</el-button>
      </span>
    </template>
  </el-dialog>

  <el-dialog v-model="addBleDeviceVisible"  class="myclass" title="BLE设备" width="70%">
    <el-select class="type-select" v-model="bleDevice.gateway_id" placeholder="未选择" size="large">
      <el-option v-for="gateway in gatewayList" :key="gateway.id" :label="gateway.name" :value="gateway.id"/>
    </el-select>
    <template #footer>
      <span class="dialog-footer">
        <el-button @click="addBleDeviceVisible = false">取消</el-button>
        <el-button type="primary" @click="configBleDevice">确认</el-button>
      </span>
    </template>
  </el-dialog>
  
  <el-dialog v-model="configBleDeviceVisible" title="输入配置信息" width="70%">
    <span>
      服务UUID：
      <el-input class="device-input" v-model="bleDevice.svr_uuid" placeholder="请输入" size="large"/>
    </span>
    <span>
      特征UUID：
      <el-input class="device-input" v-model="bleDevice.char_uuid" placeholder="请输入" size="large"/>
    </span>
    <template #footer>
      <span class="dialog-footer">
        <el-button @click="configBleDeviceVisible = false">取消</el-button>
        <el-button type="primary" @click="createBleDevice">确认</el-button>
      </span>
    </template>
  </el-dialog>

  <el-dialog v-model="addMqttDeviceVisible" title="MQTT设备" width="70%">
    <h1>设备ID：{{mqttDevice.device_id}}</h1>
    <h1>验证码：{{mqttDevice.authcode}}</h1>

    <template #footer>
      <span class="dialog-footer">
        <el-button @click="addMqttDeviceVisible = false">取消</el-button>
        <el-button type="primary" @click="">确认</el-button>
      </span>
    </template>
  </el-dialog>

  <el-dialog v-model="addHttpDeviceVisible" title="HTTP设备" width="70%">
    <span>
      HTTP链接
      <el-input class="device-input" v-model="httpDevice.http_link" placeholder="请输入" size="large"/>
    </span>
    <template #footer>
      <span class="dialog-footer">
        <el-button @click="addHttpDeviceVisible = false">取消</el-button>
        <el-button type="primary" @click="configHttpDevice">确认</el-button>
      </span>
    </template>
  </el-dialog>

</template>

<script setup>
  import { ref,reactive,nextTick } from "vue";
  import request  from '../utils/request.js';
  import { ElMessage,ElMessageBox   } from 'element-plus';

  const emit = defineEmits(['refreshList','mqttBroadcast']);
  const refresh = ()=>{
    emit("refreshList",'1');
  }

  const publish = (id,data)=>{
      emit("mqttBroadcast",id,data)
  }

  const typeList = ref([])
  const gatewayList = ref([])

  var selectedType = reactive({
    type_id:null,
    add:"",
  })

  const addDeviceVisible = ref(true);
  const addBleDeviceVisible = ref(false)
  const addMqttDeviceVisible = ref(false)
  const addHttpDeviceVisible = ref(false)
  const configBleDeviceVisible = ref(false)
  
  const bleDevice = reactive({
    type_id:null,
    device_id:null,
    gateway_id:null,
    svr_uuid: null,
    char_uuid: null,
  })

  const mqttDevice = reactive({
    type_id:null,
    device_id: null,
    authcode: '000000',
  })

  const httpDevice = reactive({
    type_id:null,
    http_link: null,
  })

  const addDeviceByType = () => {
    for(var type of typeList.value){
      if(type.id === selectedType.type_id){
        selectedType.add = type.add
        break
      }
    }

    addDeviceVisible.value = false
    switch(selectedType.add){
      case "ble":
        addBleDeviceVisible.value = true
        break
      case "mqtt":
        configMqttDevice()
        addMqttDeviceVisible.value = true
        break
      case "http":
        addHttpDeviceVisible.value = true
        break
    }
  }

  const configBleDevice = () => {
    addBleDeviceVisible.value = false
    configBleDeviceVisible.value = true
  }

  const createBleDevice = () => {
    publish(bleDevice.gateway_id,{
      request:"ble_tryconnect",
      svr_uuid: bleDevice.svr_uuid,
      char_uuid: bleDevice.char_uuid
    })
  }

  const configMqttDevice = () => {
    request.post("/device",{type_id:selectedType.type_id}).then((res) => {
      if(res.data.message === true){
        mqttDevice.device_id = res.data.data.device_id
        request.put("/auth/authcode",{device_id:mqttDevice.device_id}).then((res) => {
          mqttDevice.authcode = res.data.data.authcode
        })
      }else{
        ElMessage({
          message: '初始化设备失败',
          type: 'error',
          grouping:true
        })
      }
    })
  }

  const configHttpDevice = () => {

  }

  const addPageMethod = ()=>{
    addDeviceVisible.value = true;
  }

  const mhs = (msg) =>{
    switch(msg.data.response){
      case "ble_tryconnect":
        if(msg.data.return === "true"){
          request.post("/device",{type_id:selectedType.type_id}).then((res) => {
            if(res.data.message === true){
              bleDevice.device_id = res.data.data.device_id
              publish(bleDevice.gateway_id,{
                request:"ble_add",
                id:bleDevice.device_id,
                svr_uuid:bleDevice.svr_uuid,
                char_uuid:bleDevice.char_uuid
              })
            }else{
              return false
            }
          })
        }
        break
      case "ble_add":
        if(msg.data.return === "true"){
          ElMessage({
            message: '添加成功',
            type: 'success',
            grouping:true
          })
        }else{
          ElMessage({
            message: '添加失败',
            type: 'error',
            grouping:true
          })
        }
        break
      case "mqtt_add":
        if(msg.data.return === "true"){
          ElMessage({
            message: '添加成功',
            type: 'success',
            grouping:true
          })
        }else{
          ElMessage({
            message: '添加失败',
            type: 'error',
            grouping:true
          })
        }
        break
    }
    console.log(msg)
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
  getGatewayList()

  const createDevice = (type_id) => {
    request.post("/device",{type_id}).then((res) => {
      if(res.data.message === true){
        ElMessage({
          message: '添加成功',
          type: 'success',
          grouping:true
        })
        refresh();
        return res.data.data.device_id
      }else{
        ElMessage({
          message: '添加失败',
          type: 'error',
          grouping:true
        })
        return false
      }
    })
  }

  defineExpose({addPageMethod,mhs});
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