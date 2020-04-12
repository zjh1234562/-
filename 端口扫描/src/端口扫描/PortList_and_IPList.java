package ¶Ë¿ÚÉ¨Ãè;

import java.util.ArrayList;
import java.util.List;

public class PortList_and_IPList {
    static private List<Integer> OpenPortList=new ArrayList<>();
    //static private List<String> ipList=new ArrayList();

    synchronized  public void addPort(int port){
        OpenPortList.add(port);
    }

    public Boolean clearPortList(){
        OpenPortList.clear();
        return true;
    }

   public List<Integer> getOpenPortList() {
       return OpenPortList;
   }
   
//   synchronized public void addIP(String ip) {
//	    ipList.add(ip); 
//}



}
