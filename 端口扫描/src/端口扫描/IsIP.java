package �˿�ɨ��;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class IsIP {
    //�������IP��ַ���м��
    public static String testIp(String startIp, String endIp) {
        //ƥ���ַ����Ƿ�ΪIP��ַ
        Pattern ipPattern = Pattern.compile("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
        //ƥ���ַ����Ƿ�ΪURL
        Pattern urlPattern = Pattern.compile("[\\w\\-_]+(\\.[\\w\\-_]+)+([\\w\\-\\.,@?^=%&amp;:/~\\+#]*[\\w\\-\\@?^=%&amp;/~\\+#])?");
        if (startIp.trim().equals("") && endIp.trim().equals("")) {
            return "IP��ַ����Ϊ�գ�";
        } else if (startIp.trim().equals("")) {
            return "IP��ַ�ο�ʼ���ֲ���Ϊ�գ�";
        } else if (endIp.trim().equals("")) {
            if (urlPattern.matcher(startIp).matches()) {
                return "url";
            } else {
                return "�������IP��ַ��ʽ����ȷ��";
            }
        } else {
            if (ipPattern.matcher(startIp).matches() && ipPattern.matcher(endIp).matches()) {
                for (int i = 0; i < 3; i++) {
                    //IP��ַǰ��λ����ͬ
                    if (!(startIp.split("\\.")[i].equals(endIp.split("\\.")[i]))) {
                        return "IP��ַǰ��λ����ͬ";
                    }
                }
                int start = Integer.valueOf(startIp.split("\\.")[3]);
                int end = Integer.valueOf(endIp.split("\\.")[3]);
                if (start > end) {
                    return "IP��ַ�θ�ʽ����ȷ��";
                }
                return "ip";
            } else {
                return "�������IP��ַ��ʽ����ȷ��";
            }
        }
    }
    
    //���������IP��ַ��Χȷ�������IP��ַ
    public static void scanIp(String startIp, String endIp, Set<String> ipSet) {
        String base = startIp.split("\\.")[0] + "." + startIp.split("\\.")[1] + "." + startIp.split("\\.")[2];
        int start = Integer.valueOf(startIp.split("\\.")[3]);
        int end = Integer.valueOf(endIp.split("\\.")[3]);
        for (int i = start; i <= end; i++) {
            ipSet.add(base + "." + i);
        }
    }
    
    public static String findServiceByPort(int port) {
        String str;
        File f = new File("PortData.txt");
        FileInputStream fis = null;
        InputStreamReader isr = null;
        BufferedReader br = null;
        try {
            fis = new FileInputStream(f);
            isr = new InputStreamReader(fis, "UTF-8");
            br = new BufferedReader(isr);
            while ((str = br.readLine()) != null) {
                String b = str.split(" ")[1].split("=")[0];//�˿ں�
                int p = Integer.valueOf(b);
                if (p == port) {
                    return str;
                }
            }
            return "";
        } catch (IOException e) {
            e.printStackTrace();
            return "";
        } finally {
            try {
                if (fis != null) {
                    fis.close();
                }
                if (isr != null) {
                    isr.close();
                }
                if (br != null) {
                    br.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    public static void main(String[] args) {
		System.out.println(findServiceByPort(707));
	}
    




    
    

}
