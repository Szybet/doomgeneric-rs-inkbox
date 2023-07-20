use std::io::Read;

use doomgeneric::doom::{self, KeyData};
struct Game {}

use std::{thread, time};

impl doom::Doom for Game {
    fn draw_frame(&mut self, screen_buffer: &[u32], xres: usize, yres: usize) {
        let path = "/tmp/doom_image";
        if std::path::Path::new(path).exists() {
            return;
        }
        let mut screen_buffer_rgba: Vec<u8> = Vec::with_capacity(xres * yres * 4);
        for argb in screen_buffer {
            screen_buffer_rgba.push(((argb >> 16) & 0xFF) as u8);
            screen_buffer_rgba.push(((argb >> 8) & 0xFF) as u8);
            screen_buffer_rgba.push(((argb >> 0) & 0xFF) as u8);
            // Alpha seems to be opacity. Inverting it.
            screen_buffer_rgba.push(((argb >> 24) & 0xFF) as u8);
        }

        let mut file = std::fs::File::create(path).unwrap();
        std::io::Write::write_all(&mut file, &screen_buffer_rgba).unwrap();
        file.sync_all().unwrap();
    }
    fn get_key(&mut self) -> Option<doom::KeyData> {
        thread::sleep(time::Duration::from_millis(10));
        let path = "/tmp/doom_control";
        let path_stop  = "/tmp/doom_control_stop";
        let mut key: u8 = 0;
        if std::path::Path::new(path).exists() {
            let mut contents = String::new();
            {
                let mut file = std::fs::File::open(path).unwrap();
                let _ = file.read_to_string(&mut contents);
            }
            let _ = std::fs::remove_file(path);
            contents = contents.replace('\n', "");
            contents = contents.replace('\r', "");
            
            if contents.is_empty() {
                return None;
            }
            if contents == "right" {
                key = unsafe { doom::key_right as u8 };
                println!("Received key: key_right");
            }
            if contents == "left" {
                key = unsafe { doom::key_left as u8 };
                println!("Received key: key_left");
            }
            if contents == "up" {
                key = unsafe { doom::key_up as u8 };
                println!("Received key: key_up");
            }
            if contents == "down" {
                key = unsafe { doom::key_down as u8 };
                println!("Received key: key_down");
            }
            if contents == "fire" {
                key = unsafe { doom::key_fire as u8 };
                println!("Received key: key_fire");
            }
            if contents == "esc" {
                key = 27;
                println!("Received key: esc");
            }
            if contents == "enter" {
                key = b'\r';
                println!("Received key: enter");
            }
            if contents == "straf" {
                key = unsafe { doom::key_strafe as u8 };
                println!("Received key: key_strafe");
            }
            if contents == "use" {
                key = unsafe { doom::key_use as u8 };
                println!("Received key: key_use");
            }

            let keydata = KeyData { pressed: true, key };
            Some(keydata)
        } else if std::path::Path::new(path_stop).exists() {
                let mut contents = String::new();
            {
                let mut file = std::fs::File::open(path_stop).unwrap();
                let _ = file.read_to_string(&mut contents);
            }
            let _ = std::fs::remove_file(path_stop);
            contents = contents.replace('\n', "");
            contents = contents.replace('\r', "");
            
            if contents.is_empty() {
                return None;
            }
            if contents == "right_stop" {
                key = unsafe { doom::key_right as u8 };
                println!("Received key: right_stop");
            }
            if contents == "left_stop" {
                key = unsafe { doom::key_left as u8 };
                println!("Received key: left_stop");
            }
            if contents == "up_stop" {
                key = unsafe { doom::key_up as u8 };
                println!("Received key: up_stop");
            }
            if contents == "down_stop" {
                key = unsafe { doom::key_down as u8 };
                println!("Received key: down_stop");
            }
            if contents == "fire_stop" {
                key = unsafe { doom::key_fire as u8 };
                println!("Received key: fire_stop");
            }
            if contents == "use_stop" {
                key = unsafe { doom::key_use as u8 };
                println!("Received key: use_stop");
            }
            let keydata = KeyData { pressed: false, key };
            Some(keydata)
        } else {
            None
        }
    }
    fn set_window_title(&mut self, title: &str) {}
}

fn main() {
    doom::init(Game {});
}
