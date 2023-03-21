use std::io;
fn main() {
    let mut input = String::new();
    let mut a = [0;6];
    let mut cur=0;
    println!("请输入6个数");
    // 读取
    // 使用循环保证读取到6个数才会开始运行
    loop {
        input.clear();  // 清除之前读取的内容
        io::stdin().read_line(&mut input).unwrap();
        let b: Vec<i32> = input
            .split_whitespace()
            .map(|v| v.parse::<i32>().expect("请只输入数字"))
            .collect();
        for v in b {
            a[cur] = v;
            cur+= 1;
            if cur == a.len() {
                break;
            }
        }
        if cur == a.len() {
            break;
        }
    }
    // 输出
    println!("==============");
    for i in 0..a.len() {
        for j in 0..a.len() {
            print!("{} ",a[(j + a.len() -i)%a.len()])
        }
        println!("");
    }

}

