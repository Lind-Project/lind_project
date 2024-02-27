
#![feature(once_cell)]
use std::env;
pub mod pipe;
use crate::pipe::EmulatedPipe;
pub use std::thread::spawn;
const PIPE_SIZE: usize = 65535;
use std::sync::Arc;
pub use std::sync::{LazyLock};
use parking_lot::Mutex;

pub const TOTALSIZE : usize = usize::pow(2, 34);

pub static READFD: LazyLock<Arc<Mutex<Option<EmulatedPipe>>>> =
    LazyLock::new(|| Arc::new(Mutex::new(None))); 
pub static WRITEFD: LazyLock<Arc<Mutex<Option<EmulatedPipe>>>> =
    LazyLock::new(|| Arc::new(Mutex::new(None))); 

fn write_syscall(bufptr: *const u8, writebuf: usize) -> usize {
    let writeopt = WRITEFD.lock();
    let writepipe = writeopt.as_ref().unwrap();
    let ret = writepipe.write_to_pipe(bufptr, writebuf) as usize;
    ret
}

fn read_syscall(bufptr: *mut u8, readbuf: usize) -> usize {
    let readopt = READFD.lock();
    let readpipe = readopt.as_ref().unwrap();
    let ret = readpipe.read_from_pipe(bufptr, readbuf) as usize;
    ret
}

fn main() {

    let args: Vec<String> = env::args().collect();

    let writesize = args[1].parse::<u32>().unwrap();
    let readsize= args[2].parse::<u32>().unwrap();
    let writebuf: usize = usize::pow(2, writesize);
    let readbuf: usize = usize::pow(2, readsize);   

    let num_writes = TOTALSIZE/writebuf;

    let pipe = pipe::new_pipe(PIPE_SIZE);

    let mut readopt = READFD.lock();
    let _ret1 = readopt.insert(pipe.clone());

    let mut writeopt = WRITEFD.lock();
    let _ret2 = writeopt.insert(pipe.clone());

    drop(readopt);
    drop(writeopt);

    let writer = std::thread::spawn(move || {

        let mut buf: Vec<u8> = Vec::with_capacity(writebuf);
        let bufptr = buf.as_mut_ptr();
        unsafe { buf.set_len(writebuf); }

        for _i in 0..num_writes {
            let _ret = write_syscall(bufptr, writebuf);
        }

        let writeopt = WRITEFD.lock();
        let writepipe = writeopt.as_ref().unwrap();
        writepipe.set_eof();
    });


    let reader = std::thread::spawn(move || {

        let mut bytes_read: usize = 1;

        let mut buf: Vec<u8> = Vec::with_capacity(readbuf);
        unsafe { buf.set_len(readbuf); }

        let bufptr = buf.as_mut_ptr();
        while bytes_read != 0 {
            bytes_read = read_syscall(bufptr, readbuf);
        }


    });

    writer.join().unwrap();
    reader.join().unwrap();
}

