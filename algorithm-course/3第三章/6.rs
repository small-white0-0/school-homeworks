use std::io;
fn main() {
    println!("PS: 该程序无法处理不正确的数学表达式。不正确的四则运算，结果是未定义的.");
    println!("PS: a+(b) 与 a +((c)) 这种，我们不认为其是正确的算式.");
    println!("请输入正确的数学表达式:");
    // 输入计算式
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("未知错误");

    // 先考虑括号前
    // 除法‘/’  =》括号不能去
    // 减法 ‘-’  =》括号不能去
    // 加法和乘法，无符号 =》？？

    // 括号内
    // 括号前是乘法，如果括号内有加减法 =》括号不能去
    // 括号前是乘法，括号内无加减法 =》 ？？
    // 括号前是加法或无符号，括号内有任意符号 =》 ？？

    // 括号后
    // 括号前是乘法，括号内无加减法，括号后任意符号 =》可以去除
    // 括号前是加法或无符号，括号内有任意符号，括号后是加减法或无符号 =》可以去除
    // 括号前是加法或无符号，括号内有任意符号，括号后是乘除法 =》 ？？

    // 针对 括号前是加法或无符号，括号内有任意符号，括号后是乘除法 的讨论
    // 括号前是加法或无符号，括号内有加减法，括号后是乘除法 =》 括号不能去
    // 括号前是加法或无符号，括号内无加减法，括号后是乘除法 =》 括号可以去除

    // 总结
    // 括号前是乘法，括号内无加减法，括号后任意符号 =》可以去除
    // 括号前是加法或无符号，括号内有任意符号，括号后是加减法或无符号 =》可以去除
    // 括号前是加法或无符号，括号内无加减法，括号后是乘除法 =》 括号可以去除

    // PS 为了简化括号前后无运算符号的情况，使用 ‘#’ 作为无符号的替代

    let mut equation_without_space = input.split_whitespace().collect::<String>();
    // 加上#
    equation_without_space.insert_str(0, "#");
    equation_without_space.push_str("#");

    let mut equation: Vec<char> = equation_without_space.chars().collect();
    // 开始处理
    for i in 0..equation.len() {
        if equation[i] == '(' {
            // 获取带括号的算式
            let part_equation = get_part_equation(&equation, i).expect("算式解析错误");
            // 左右括号下标
            let left_brackets_index = i;
            let right_brackets_index = i+part_equation.len() -1;
            // 括号前后的运算符
            let left_operation = get_left_operation(&equation, left_brackets_index-1).expect("解析算式错误");
            let right_operation = get_right_operation(&equation, right_brackets_index+1).expect("解析算式错误");

            // 判断是否可以去除
            if is_can_remove(part_equation,
                 left_operation,
                 right_operation) {
                    // 用空格替换可以去除的括号
                    equation[left_brackets_index] = ' ';
                    equation[right_brackets_index] = ' ';
            }
        }
    }

    // 输出处理后的算式
    println!("去除多于括号之后的：{}",equation[1..equation.len()-1].into_iter().filter(|v| **v!=' ').collect::<String>());

}

// 使用函数获取括号前后的运算符号
// 主要是跳过空白符号
fn get_left_operation(equation: &[char],start: usize)->Result<char,()> {

    for i in (0..=start).rev() {
        match equation[i] {
            ' '=>continue,
            '+'|'-'|'*'|'/'|'#'|'('=>return Ok(equation[i]),
            _ =>break,
        }
    }
    Err(())
}

fn get_right_operation(equation: &[char],start: usize)->Result<char,()>{

    for i in start..equation.len() {
        match equation[i] {
            ' '=>continue,
            '+'|'-'|'*'|'/'|'#'|')'=>return Ok(equation[i]),
            _ =>break,
        }
    }
    Err(())
}

fn get_part_equation<'a>(equation: &'a [char],start:usize)-> Option<&'a [char]> {
    let mut count = 0;
    let mut end=0;
    for i in start..equation.len() {
        if equation[i] == '(' {
            count += 1;
        }else if  equation[i] == ')' {
            count -=1;
        }

        if count == 0 {
            end = i;
            break;
        }
    }

    if count == 0 && end > start {
        Some(&equation[start..=end])
    }else{
        None
    }

}

fn is_can_remove(part_equation: &[char], left_operator: char, right_operator: char) -> bool {
    match (left_operator, right_operator) {
        ('*', _) if !has_add_or_sub(part_equation) => true,
        ('+' | '#'|'(', '+' | '-' | '#'|')') => true,
        ('+' | '#'|'(', '*' | '/') if !has_add_or_sub(part_equation) => true,
        (_, _) => false,
    }
}

fn has_add_or_sub(part_equation: &[char]) -> bool {
    part_equation.contains(&'+') || part_equation.contains(&'-')
}

