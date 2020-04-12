package hhjk;

import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
 
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import javax.swing.WindowConstants;

public class LoginPanell extends JFrame {
	JLabel jl1;
	JLabel jl2;
	
	public void init() {
		setTitle("请登陆");
		setLayout(null);
		// 定义一个容器
		Container c = getContentPane();
		// 创建"用户名:"标签
		jl1 = new JLabel("用户名：");
		// 创建文本框
		final JTextField jtf1 = new JTextField();
		// 创建"密码:"标签
		jl2 = new JLabel("密码:");
		// 创建密码框
		final JPasswordField jpf1 = new JPasswordField();
		// 设置密码字符为*
		jpf1.setEchoChar('*');
		// 创建"提交"按钮
		JButton jb1 = new JButton("提交");
		// 创建"重置"按钮
		JButton jb2 = new JButton("重置");
		jb1.addActionListener(new ActionListener() {
 
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				
					if (((jtf1.getText().trim().equals("小明") && new String(jpf1.getPassword()).trim().equals("mrsoft")))
							||((jtf1.getText().trim().equals("小军") && new String(jpf1.getPassword()).trim().equals("mrsoft")))
							||((jtf1.getText().trim().equals("小红") && new String(jpf1.getPassword()).trim().equals("mrsoft")))) {
						JOptionPane.showMessageDialog(null, "登陆成功！");
						destory();
						Mainwindows mainwindows=new Mainwindows();
						mainwindows.init(jtf1.getText());
						
					} else if (jtf1.getText().trim().length() == 0 || new String(jpf1.getPassword()).trim().length() == 0) {
						JOptionPane.showMessageDialog(null, "不能为空!");
					} else {
						JOptionPane.showMessageDialog(null, "错误");
						// 清零
						jtf1.setText("");
						jpf1.setText("");
					}
					

			}
		});
		// 实现"重置"按钮功能
		jb2.addActionListener(new ActionListener() {
 
			@Override
			public void actionPerformed(ActionEvent arg0) {
				// TODO Auto-generated method stub
				jtf1.setText("");
				jpf1.setText("");
 
			}
		});
		// 将各组件添加到容器中
		c.add(jl1);
		c.add(jtf1);
		c.add(jl2);
		c.add(jpf1);
		c.add(jb1);
		c.add(jb2);
		// 设置各组件的位置以及大小
		jl1.setBounds(10, 20, 90, 30);
		jtf1.setBounds(60, 20, 210, 30);
		jl2.setBounds(25, 60, 90, 30);
		jpf1.setBounds(60, 60, 210, 30);
		jb1.setBounds(80, 100, 60, 40);
		jb2.setBounds(150, 100, 60, 40);
		// 设置窗体大小、关闭方式、不可拉伸
		setSize(300, 220);
		setVisible(true);
		setResizable(true);
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		//return jtf1.getText();
		
	}	
	
	public void destory() {
		setVisible(false);
	}

	public static void main(String[] args) {
		LoginPanell loginPanel=new LoginPanell();
		loginPanel.init();
		
	}

}
