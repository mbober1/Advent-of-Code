use std::fs;

const ALSO_NUMBERS: [&str; 9]= ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];

fn get_first_number(line : &str) -> (usize, u32)
{
    for (idx, letter) in line.chars().enumerate() {
        
        let digit = letter.to_digit(10);

        if digit.is_some() {
            let result = digit.unwrap();
            return (idx, result);
        }
    }

    (line.len(), 0)
}

fn get_last_number(line : &str) -> (usize, u32)
{
    let mut result: u32 = 0;
    let mut max_idx: usize = 0;

    for (idx, letter) in line.chars().enumerate() {
        
        let digit = letter.to_digit(10);

        if digit.is_some() {
            if idx > max_idx {
                result = digit.unwrap();
                max_idx = idx;
            }
        }
    }

    (max_idx, result)
}

fn get_first_fake_number(line : &str) -> (usize, u32) {
    let mut iter: u32 = 0;
    let mut result: u32 = 0;
    let mut min_idx: usize = line.len();

    for fake_num in ALSO_NUMBERS {
        let idx: Option<usize> = line.find(fake_num);
        iter = iter + 1;

        if idx.is_some() {
            if idx.unwrap() < min_idx {
                result = iter;
                min_idx = idx.unwrap();
            }
        }
    }

    (min_idx, result)
}

fn get_last_fake_number(line : &str) -> (usize, u32) {
    let mut iter: u32 = 0;

    let mut result: u32 = 0;
    let mut max_idx: usize = 0;

    for fake_num in ALSO_NUMBERS {
        let idx: Option<usize> = line.rfind(fake_num);
        iter = iter + 1;

        if idx.is_some() {
            if idx.unwrap() > max_idx {
                result = iter;
                max_idx = idx.unwrap();
            }
        }
    }

    (max_idx, result)
}


fn main() {
    let mut result = 0;

    for line in fs::read_to_string("input").unwrap().lines()
    {
        let mut sub_result = 0;
        let first_digit = get_first_number(line);
        let first_fake_number = get_first_fake_number(line);


        let last_digit = get_last_number(line);
        let last_fake_number = get_last_fake_number(line);

        if first_digit.0 == last_digit.0 && first_fake_number.1 == 0 && last_fake_number.1 == 0 {
            println!("drop {line}");
            continue;
        }

        if first_digit.0 < first_fake_number.0 {
            sub_result += first_digit.1*10;
        }
        else {
            sub_result += first_fake_number.1*10;
        }

        if last_digit.0 > last_fake_number.0 {
            sub_result += last_digit.1;
        }
        else {
            sub_result += last_fake_number.1;
        }

        let dupa0 =first_digit.1;
        let dupa1 =first_fake_number.1;
        let dupa2 =last_digit.1;
        let dupa3 =last_fake_number.1;
        
        result += sub_result;
        println!("first_digit: {dupa0}, first_fake_number: {dupa1}, last_digit: {dupa2}, last_fake_number: {dupa3} -> Result {sub_result} for {line}")
    }

    println!("Result: {result}");
}
