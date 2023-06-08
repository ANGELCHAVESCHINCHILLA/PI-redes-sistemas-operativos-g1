//

const MAP = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const getSalt = (length) => {
    let salt = '';

    for (let index = 0; index < length; index++) {
        const random_number = Math.floor(Math.random() * Hash.MAP.length);
        salt += Hash.MAP[random_number];
    }

    return salt;
}

// Add user

const add_user_id = document.querySelector("#add_user_id");
const add_user_name = document.querySelector("#add_user_name");
const add_user_job_name = document.querySelector("#add_user_job_name");
const add_user_email = document.querySelector("#add_user_email");
const add_user_phone_number = document.querySelector("#add_user_phone_number");
const add_user_type = document.querySelector("#add_user_type");

const add_user_send_button = document.querySelector("#add_user_send_button");

add_user_send_button.addEventListener('click', () => {

});

// Remove user

// Edit user
