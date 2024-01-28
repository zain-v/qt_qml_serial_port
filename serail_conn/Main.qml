import QtQuick
import QtQuick.Controls
import mylib
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    Button{
        x:100
        y:250
        text: "connect"
        onClicked: {
            srl.connection()
        }
    }

    Rectangle{
        id:led
        x:10
        y:10
        width: 10
        height: 10
        radius: 5
        color: "#ff0000"
    }
    Text{
        id:show_data
        x:50
        y:100
        text:"---------------------"
    }

    Text{
        id:show_info
        x:50
        y:130
        text:"---------------------"
    }
    Timer {
        id:timer
        interval: 500; running: false; repeat: true
        onTriggered: srl.sendData("z")
    }
    Ser{
        id:srl
        onIs_connected: (conn)=>{
            if(conn){
                led.color ="#00ff00"
            }else{
                led.color = "#ff0000"
            }
            timer.running = conn;
        }

        onArduioData:(data)=>{
            show_data.text = data;
             // console.log("from arduino ",data)
        }
        onShow_info:(info) =>{
           show_info.text=info;
        }
    }
}
