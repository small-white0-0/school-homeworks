use std::{io, ops::{Add, Mul}, fmt::Display};

fn sum_with_limit(n: u8) -> Result<u64, &'static str> {
    if n > 19 {
        return Err("n超出最大限制19");
    }
    let mut sum = 0;
    let mut current_number = 0;
    for _i in 1..=n {
        current_number = current_number * 10 + 2;
        sum += current_number;
    }
    Ok(sum)
}

fn sum_without_limit(n:u8)->String {
    let mut sum:BigNumber = BigNumber::new(0);
    let mut current_number:BigNumber = BigNumber::new(0);
    let two = BigNumber::new(2);
    for _i in 1..=n {
        current_number = current_number * 10 + &two;
        sum = sum +  &current_number;
    }
    sum.to_string()
}

// 一个简单的大数类
#[derive(Clone)]
struct BigNumber {
    // 利用数组记录0-9的数字串
    number: Vec<u8>,
}

// 实现最简单的从字符串创建 BigNumber
impl BigNumber {
   fn new(number:u32)->Self {
        let s:&str = &number.to_string();
        s.into()
    }
}
impl From<&str> for BigNumber {
    fn from(value: &str) -> Self {
        // 解析数字串
        let result:Vec<u8> = value.chars().map(|v| {
            if v < '0' || v > '9' {
                panic!("字符串不是纯数字的")
            }
            v as u8-'0' as u8
        }).collect();

        BigNumber { number: result }
    }
}

// 实现类型转字符串的方法
impl Display for BigNumber {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let mut v: Vec<u8> = self.number.iter().map(|v| v + '0' as u8).collect();
        v.reverse();
        write!(f,"{}",String::from_utf8_lossy(&v))
    }
}

// 下面只重载在求和中需要用到的运算符
// 重载 + 号运算符号
impl Add<&Self> for BigNumber {
    type Output = Self;

    fn add(self, other: &Self) -> Self::Output {
        let max_len = if self.number.len() > other.number.len() {
            self.number.len()
        }else{
            other.number.len()
        };

        let mut sum: Vec<u8> = vec![];
        // 上一次的进位和
        let mut c = 0;
        for i in 0..max_len {
            let a = self.number.get(i).or(Some(&0)).unwrap();
            let b = other.number.get(i).or(Some(&0)).unwrap();
            sum.push((a+b+c)%10);   // 记录当前位的数字和的各位
            c = (a+b+c)/10;         // 记录进位
        }
        // 说明两个数的和超出了长度,记录最后的非0进位
        if c > 0{
            sum.push(c);
        }
        return BigNumber { number: sum };
    }
}

// 重载乘法运算符号
// 这里为了简化重载难度，只接受一个 i32 类型的数作为乘法运行的右边数字
impl Mul<i32> for BigNumber {
    type Output = Self;

    fn mul(self, other: i32) -> Self::Output {
        let mut value = "0".into();
        let mut count = other;
        loop {
            value = value + &self;
            count -= 1;
            if count == 0 {
                break;
            }
        }
        value
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n = input.trim().parse::<u8>().unwrap();
    println!("====快速，有长度限制的===");
    match sum_with_limit(n) {
        Ok(result) => println!("求和结果是:{}", result),
        Err(msg) => println!("{}", msg),
    }
    println!("===慢，但是无长度限制的===");
    println!("求和结果是:{}",sum_without_limit(n));
}
