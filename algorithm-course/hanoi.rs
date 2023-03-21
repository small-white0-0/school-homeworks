// #[link(name="test", kind="static")]
extern "C" {
    fn hanoi(n:i32, a: u8,b:u8, c:u8);
}

fn main(){
   
   unsafe{ 
    hanoi(3,'a' as u8,'b' as u8,'c' as u8);
   }

}