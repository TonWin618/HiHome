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

    var iframeRef = ref(null)
    var iframeWindow = null

    const loadEvent = () => {
        iframeWindow = iframeRef.value.contentWindow
    }
    const emit = defineEmits(['mqttBroadcast']);
    const publish = (data)=>{
        emit("mqttBroadcast",props.device.id,data)
    }

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
    const mhs = (msg) => {
        console.log("control panel received")
        if(msg.id === props.device.id){
            iframeWindow.postMessage(msg.data,"*")
        }
    }
    defineExpose({setVisible,mhs});

    onMounted(()=>{
        //监听iframe页面
        window.addEventListener('message',(event) => {
            var msg = event.data
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
</script>