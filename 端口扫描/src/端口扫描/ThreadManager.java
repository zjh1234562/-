package 端口扫描;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.JProgressBar;

import 端口扫描.ScanportThread;

public class ThreadManager {
    private List<Integer> PortList=new ArrayList<>();
    private List<ScanportThread> ThreadList=new ArrayList<>();
    private int n=0;
    public void setPortList(List<Integer> portList) {
        PortList = portList;
    }

    public Boolean setIP(String IP){
        try{
            String ip = "^(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|[1-9])\\."
                    +"(00?\\d|1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)\\."
                    +"(00?\\d|1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)\\."
                    +"(00?\\d|1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)$";
            Pattern pattern = Pattern.compile(ip);
            Matcher matcher = pattern.matcher(IP);
            return matcher.matches();
        } catch (Exception e) {
            return false;
        }
    }
//    
//    //根据输入的IP地址范围确定具体的IP地址
//    public static void scanIp(String startIp, String endIp, Set<String> ipSet) {
//        String base = startIp.split("\\.")[0] + "." + startIp.split("\\.")[1] + "." + startIp.split("\\.")[2];
//        int start = Integer.valueOf(startIp.split("\\.")[3]);
//        int end = Integer.valueOf(endIp.split("\\.")[3]);
//        for (int i = start; i <= end; i++) {
//            ipSet.add(base + "." + i);
//        }
//    }

    public List<Integer> changeToList(String list){
        String[] listarr=list.split(",");
        List<Integer> result=new ArrayList<>();
        for(String Item:listarr){
            result.add(Integer.parseInt(Item));
        }
        return result;
    }

    public String setLocalHostIP(){
        try {
            InetAddress ip=InetAddress.getLocalHost();
            String[] arr=ip.toString().split("/");
            return arr[1];
        } catch (UnknownHostException e) {
            return "error";
        }
    }

    public void ThreadDilivery(List<Integer> portList,String IP,int blocksize,int n,JProgressBar bar){
        setPortList(portList);
        List<List<Integer>> DiliveryList=subList(PortList,blocksize);
        for(List<Integer> Item:DiliveryList){
        	System.out.println(Item);
            ScanportThread thread=new ScanportThread();
            thread.setPortList(Item);
            thread.setIP(IP);
            thread.setprobar(bar);
            ThreadList.add(thread);
        }
    }

    public void run(){
            for(ScanportThread Item:ThreadList){
                Item.start();
            }
    }

    public Boolean isDone(){
        for(ScanportThread Item:ThreadList){
            if(Item.isAlive()){
                return false;
            }
        }
        return true;
    }



    List<List<Integer>> subList(List<Integer> PortList,int BlockSize){
        List<List<Integer>> result=new ArrayList<>();
        if(BlockSize>PortList.size()){
            result.add(PortList);
        }else {
            int batchSize = PortList.size() / BlockSize;
            int remain = PortList.size() % BlockSize;
            for (int i = 0; i < batchSize; i++) {
                int fromIndex = i * BlockSize;
                int toIndex = fromIndex + BlockSize;
                result.add(PortList.subList(fromIndex, toIndex));
            }
            if(remain>0){
                result.add(PortList.subList(PortList.size()-remain, PortList.size()));
            }
        }
        return result;
    }



}

