use std::io;
fn main() {
    println!("请输入中心数字n。(书上的例子，可以输入3)");
    // 输入n
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("未知错误");
    let n: usize = input.trim().parse().expect("输入的字符无法解析为一个无符号的数字");

    // 两种矩阵，两个都是中心对称，第一个是偶数型行列数，第二个则是奇数行列数

    // 生成重要的左上部分的基本数
    let mut row_caches:Vec<Vec<u8>>=vec![];
    for i in 0..n {
        row_caches.push(mk_row_by_max_and_length((i+1) as u8, n));
    }
    
    // 输出第一种偶数个行列的矩阵
    // 上半部分
    for row in &row_caches {
        display(row);
        reverse_display(row);
        println!();
    }
    // 下半部分
    for row in row_caches.iter().rev(){
        display(row);
        reverse_display(row);
        println!();
    }

    println!("==================");
    // 输出第二种，奇数个行列的矩阵
    // 上半部分
    for row in &row_caches {
        display(row);
        // 逆序输出，跳过最后一个
        reverse_display(&row[..row.len()-1]);
        println!();
    }
    // 下半部分
    // 下半部分的输出，也跳过一行
    for row in row_caches.iter().rev().skip(1){
        display(row);
        // 逆序输出，跳过最后一个
        reverse_display(&row[..row.len()-1]);
        println!();
    }
    


}

fn mk_row_by_max_and_length(max:u8,length:usize)->Vec<u8>{
    let mut result = vec![];
    let mut number = 1;
    for _i in 0..length {
        result.push(number);
        if number < max {
            number += 1;
        }
    }
    result
}

// 正序输出
fn display(row: &[u8]){
    for cell in row {
        print!("{:>5}",cell);
    }
}
// 逆序输出
fn reverse_display(row: &[u8]){
    for cell in row.iter().rev() {
        print!("{:>5}",cell);
    }
}

