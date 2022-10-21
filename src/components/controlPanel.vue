<template>
    <el-dialog v-model = "visible" :title=props.device.name width="300px"  center>
        <div id="control-panel">
            <iframe sandbox="allow-scripts" @load="loadEvent" ref="iframeRef" :src="'/static/control_index/'+props.device.type_id+'.html'" width="100%" height="360px" frameborder="0">   
            </iframe>
        </div>
    </el-dialog>
</template>

<script setup>
    import { ref,reactive,onMounted  } from 'vue'
    import request  from '../utils/request.js'
    import mqtt from 'mqtt'

    //传入选中的设备信息
    const props = defineProps({
        device:{
            type: Object,
            required: true,
        }
    })
    //该页面是否显示
    const visible = ref(false)
    //交由父页面控制显示
    const setVisible = () => {
        visible.value = true;
    }
    defineExpose({setVisible});
    //
    var iframeRef = ref(null)
    var iframeWindow = null
    var client
    const options = {
        connectTimeout:4000,
        clientId:'user'+localStorage.getItem("id"),
        clean: true,
        username:'user',
        password:localStorage.getItem("token")
    }
    client = mqtt.connect("ws://127.0.0.1:8083/mqtt",options)
    const mqttMsg = () => {
        client.on("connect", (error) => {
            console.log("连接成功");
            client.subscribe(localStorage.getItem('id'), { qos: 0 }, (error) => {
                
            });
        });
        client.on("message", (topic, message) => {
            var msg = JSON.parse(message)
            if(msg.id === props.device.id){
                iframeWindow.postMessage(msg.data,"*")
            }
        });
        client.on("reconnect", (error) => {
            console.log("正在重连", error);
        });
        client.on("error", (error) => {
            console.log("连接失败", error);
        });
    }

    onMounted(()=>{
        mqttMsg();
        window.addEventListener('message',(event) => {
            var msg =event.data
            switch(msg.type){
                case "publish" : {
                    publish(msg.data)
                    break
                }
                case "getData" : {
                    getData()
                    break
                }
                case "updateData" : {
                    updateData(msg.data)
                    break
                }
                default : {
                    console.log("非有效请求")
                    break
                }
            }
        })
    })

    const loadEvent = () => {
        iframeWindow = iframeRef.value.contentWindow
    }


    const publish = (data)=>{
        var msg = {
            id:props.device.id,
            data:data
        }
        client.publish(localStorage.getItem('id'),JSON.stringify(msg),{
            qos:0, rein: false
        },(error)=>{
            
        })
    }

</script>