use std::io;
fn main() {
    println!("请输入上三角矩阵的行列数n");
    // 输入n
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("未知错误");
    let n: usize = input.trim().parse().expect("输入的字符无法解析为一个无符号的数字");

    // 左边第1列的递推关系是  F(r) = F(r-1) + r;  F(0) = 1; r从0开始到n-1。
    // 
    // 每行的第2个是第1个的 Second(r) = F(r) + r + 2;
    // 每行第3个是第2个的 Third(r) = Second(r) + r + 3;
    // 所以每行的递推关系是 G(r,c) = G(r,c-1) + r + c + 1; G(r,0) = F(r); r从0到n-1,c从0到n-r-1。

    println!("=====");
    // 每行第一个
    let mut first=1;
    for r in 0..n {
        if r == 0 {
            first = 1;
        }else{
            first += r;
        }
        let mut cur=1;
        for c in 0..n-r {
            if c == 0 {
                cur = first;
            }else{
                cur += r + c + 1;
            }
            print!("{:>4}",cur);
        }
        println!();
    }

}

