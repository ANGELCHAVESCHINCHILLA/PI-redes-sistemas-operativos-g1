//

const COMPANY_NAME = "San Jose";

const PEPPER = "Universidad de Costa Rica";

const MAP = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const getSalt = (length) => {
    let salt = '';

    for (let index = 0; index < length; index++) {
        const random_number = Math.floor(Math.random() * MAP.length);
        salt += MAP[random_number];
    }

    return salt;
}

const getHash = (password, salt) => {
    let hash = CryptoJS.SHA256(password + salt + PEPPER);

    hash = hash.toString(CryptoJS.enc.Base64);

    return hash.substring(0, 15);
};

const go_back_button = document.querySelector("#go_back_button");

go_back_button.addEventListener('click', () => {
    location.href = '/admin';
});

const user_form = document.querySelector("#user_form");

// Messages

const feedback_message = document.querySelector("#feedback_message");
const close_feedback_message = document.querySelector("#close_feedback_message");

close_feedback_message.addEventListener('click', () => {
    feedback_message.style.display = 'none';

    location.href = '/admin';
});

const error_message = document.querySelector("#error_message");
const close_error_message = document.querySelector("#close_error_message");
const error_message_content = document.querySelector("#error_message_content");

close_error_message.addEventListener('click', () => {
    error_message.style.display = 'none';
});

// Add user

const add_user_send_button = document.querySelector("#add_user_send_button");

if (add_user_send_button !== null) {
    user_form.addEventListener('submit', async (event) => {
        event.preventDefault();

        const user_id = document.querySelector("#user_id");
        const user_password = document.querySelector("#user_password");
        const user_name = document.querySelector("#user_name");
        const user_job_name = document.querySelector("#user_job_name");
        const user_email = document.querySelector("#user_email");
        const user_phone_number = document.querySelector("#user_phone_number");
        const user_type = document.querySelector("#user_type");

        const salt = getSalt(15);

        const fs_json = {
            username: user_id.value,
            password: getHash(user_password.value, salt),
            salt: salt,
            type: parseInt(user_type.value)
        };

        const db_json = {
            user: user_id.value,
            employee_name: user_name.value,
            job_name: user_job_name.value,
            company_name: COMPANY_NAME,
            email: user_email.value,
            phone_number: parseInt(user_phone_number.value),
        };

        const fs_response = await fetch("/admin/add_user/auth", {
            method: "POST",
            body: JSON.stringify(fs_json)
        });

        const db_response = await fetch("/admin/add_user/data", {
            method: "POST",
            body: JSON.stringify(db_json)
        });

        if (fs_response.status === 200 && db_response.status === 200) {
            feedback_message.style.display = 'block';
        } else {
            error_message.style.display = 'block';
            error_message_content.textContent = 'El usuario ya existe.';
        }
    });
}

// Remove user

const remove_user_send_button = document.querySelector("#remove_user_send_button");

if (remove_user_send_button !== null) {
    user_form.addEventListener('submit', async (event) => {
        event.preventDefault();

        const user_id = document.querySelector("#user_id");

        const db_json = {
            user: user_id.value,
        };

        const fs_json = {
            username: user_id.value,
        };

        const fs_response = await fetch('/admin/remove_user/auth', {
            method: 'POST',
            body: JSON.stringify(fs_json)
        })

        const db_response = await fetch("/admin/remove_user/data", {
            method: "POST",
            body: JSON.stringify(db_json)
        });

        console.log(fs_response.status);
        console.log(db_response.status);

        if (fs_response.status === 200 && db_response.status === 200) {
            feedback_message.style.display = 'block';
        } else {
            error_message.style.display = 'block';
            error_message_content.textContent = 'El usuario no existe.';
        }
    });
}

// Edit user

const edit_user_send_button = document.querySelector("#edit_user_send_button");

if (edit_user_send_button !== null) {
    user_form.addEventListener('submit', async (event) => {
        event.preventDefault();

        const user_id = document.querySelector("#user_id");
        const user_password = document.querySelector("#user_password");
        const user_name = document.querySelector("#user_name");
        const user_job_name = document.querySelector("#user_job_name");
        const user_email = document.querySelector("#user_email");
        const user_phone_number = document.querySelector("#user_phone_number");
        const user_type = document.querySelector("#user_type");

        const salt = getSalt(15);

        const fs_json = {
            username: user_id.value,
            password: getHash(user_password, salt),
            salt: salt,
            type: parseInt(user_type.value)
        };

        const db_json = {
            user: user_id.value,
            employee_name: user_name.value,
            job_name: user_job_name.value,
            company_name: COMPANY_NAME,
            email: user_email.value,
            phone_number: parseInt(user_phone_number.value),
        };

        const fs_response = await fetch('/admin/edit_user/auth', {
            method: 'POST',
            body: JSON.stringify(fs_json)
        });

        const db_response = await fetch("/admin/edit_user/data", {
            method: "POST",
            body: JSON.stringify(db_json)
        });

        console.log(fs_response.status);
        console.log(db_response.status);

        if (fs_response.status === 200 && db_response.status === 200) {
            feedback_message.style.display = 'block';
        } else {
            error_message.style.display = 'block';
            error_message_content.textContent = 'El usuario no existe.';
        }
    });
}
