use std::io;
fn main() {
    println!("请输入方阵的大小n");
    // 输入n
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("未知错误");
    let n: usize = input.trim().parse().expect("输入的字符无法解析为一个无符号的数字");

    // 记录的矩阵
    let mut matrix = vec![vec![-1;n];n];

    // 初始化
    let mut cur_loc = Location{x:0,y:0,count:0,direction:Direction::Right};
    matrix[0][0] = 1;

    // 生成数字
    loop {
        let next = get_next_location(&mut matrix, cur_loc);
        match next {
            Some(loc)=>cur_loc = loc,
            None=>break
        }
    }

    // 输出
    for r in matrix {
        for cell in r {
            print!("{:>5}",cell);
        }
        println!();
    }

}

fn get_next_location(m:&mut Vec<Vec<i32>>,cur_loc: Location)->Option<Location>{
    if cur_loc.count == 4 {
        return None;
    }
    // 让 cur_loc 可修改
    let mut cur_loc = cur_loc;

    match cur_loc.direction {
        Direction::Right=>{
            if cur_loc.x+1 < m.len() && m[cur_loc.y][cur_loc.x+1] == -1 {
                // 修改矩阵
                m[cur_loc.y][cur_loc.x+1] = m[cur_loc.y][cur_loc.x]+1;
                // 修改后的当前位置记录
                Some(Location {
                    x:cur_loc.x+1,
                    count:0,
                    ..cur_loc
                })
            }else{
                // 换向
                cur_loc.switch_direction();
                get_next_location(m, cur_loc)
            }
        },
        Direction::Down=>{
            if cur_loc.y+1<m[0].len() && m[cur_loc.y+1][cur_loc.x]==-1 {
                m[cur_loc.y+1][cur_loc.x] = m[cur_loc.y][cur_loc.x]+1;
                Some(Location {
                    y:cur_loc.y+1,
                    count:0,
                    ..cur_loc
                })
            }else{
                  // 换向
                  cur_loc.switch_direction();
                  get_next_location(m, cur_loc)
            }
        },
        Direction::Left=>{
            // 这里由于 usize 是大于等于0的，小于0会抛出数字超限的异常，
            // 所以这里是判断当前的x是否大于0,让之后的x-1不会小于0，
            // 下面y的同理
            if cur_loc.x>0 && m[cur_loc.y][cur_loc.x-1]==-1 {
                m[cur_loc.y][cur_loc.x-1] = m[cur_loc.y][cur_loc.x]+1;
                Some(Location {
                    x:cur_loc.x-1,
                    count:0,
                    ..cur_loc
                })
            }else{
                  // 换向
                  cur_loc.switch_direction();
                  get_next_location(m, cur_loc)
            }
        },
        Direction::Up=>{
            if cur_loc.y > 0 && m[cur_loc.y-1][cur_loc.x]==-1{
                m[cur_loc.y-1][cur_loc.x] = m[cur_loc.y][cur_loc.x]+1;
                Some(Location {
                    y:cur_loc.y-1,
                    count:0,
                    ..cur_loc
                })
            }else{
                  // 换向
                 cur_loc.switch_direction();
                  get_next_location(m, cur_loc)
            }
        },
    }
}

#[derive(Debug)]
struct Location{
    x:usize,
    y:usize,
    direction:Direction,
    // 记录换向次数，连续换向4次认为是到达终点
    count:u8
}
impl Location {
    fn switch_direction(&mut self){
        self.count += 1;
        self.direction = match self.direction {
            Direction::Right=>Direction::Down,
            Direction::Down=>Direction::Left,
            Direction::Left=>Direction::Up,
            Direction::Up=>Direction::Right
        }
    }
}

#[derive(Debug)]
enum Direction {
    Right,
    Down,
    Left,
    Up,
}

