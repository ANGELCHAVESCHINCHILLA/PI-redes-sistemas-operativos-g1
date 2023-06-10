//

const COMPANY_NAME = "Guachis";

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
    window.history.back();
});

// Add user

const add_user_send_button = document.querySelector("#add_user_send_button");

if (add_user_send_button !== null) {
    add_user_send_button.addEventListener('click', async () => {
        const user_id = document.querySelector("#user_id");
        const user_password = document.querySelector("#user_password");
        const user_name = document.querySelector("#user_name");
        const user_job_name = document.querySelector("#user_job_name");
        const user_email = document.querySelector("#user_email");
        const user_phone_number = document.querySelector("#user_phone_number");
        const user_type = document.querySelector("#user_type");

        const database_json = {
            user: user_id.value,
            employee_name: user_name.value,
            job_name: user_job_name.value,
            company_name: COMPANY_NAME,
            email: user_email.value,
            phone_number: parseInt(user_phone_number.value),
        };

        await fetch("/admin/add_user/data", {
            method: "POST",
            body: JSON.stringify(database_json)
        });

        const salt = getSalt(15);

        const fs_json = {
            "username": user_id.value,
            "salt": salt,
            "password": getHash(user_password, salt),
            "type": parseInt(user_type.value)
        };

        await fetch("/admin/add_user/auth", {
            method: "POST",
            body: JSON.stringify(fs_json)
        });

        location.href = "/admin";
    });
}


// Remove user

const remove_user_send_button = document.querySelector("#remove_user_send_button");

if (remove_user_send_button !== null) {
    remove_user_send_button.addEventListener('click', async () => {
        const user_id = document.querySelector("#user_id");

        const database_json = {
            user: user_id.value,
        };

        await fetch("/admin/remove_user/data", {
            method: "POST",
            body: JSON.stringify(database_json)
        });

        // REMOVING USERS IS NOT IMPLEMENTED IN THE FILE SYSTEM

        location.href = "/admin";
    });
}


// Edit user

const edit_user_send_button = document.querySelector("#edit_user_send_button");

if (edit_user_send_button != null) {
    edit_user_send_button.addEventListener('click', async () => {
        const user_id = document.querySelector("#user_id");
        const user_password = document.querySelector("#user_password");
        const user_name = document.querySelector("#user_name");
        const user_job_name = document.querySelector("#user_job_name");
        const user_email = document.querySelector("#user_email");
        const user_phone_number = document.querySelector("#user_phone_number");
        const user_type = document.querySelector("#user_type");

        const database_json = {
            user: user_id.value,
            employee_name: user_name.value,
            job_name: user_job_name.value,
            company_name: COMPANY_NAME,
            email: user_email.value,
            phone_number: parseInt(user_phone_number.value),
        };

        await fetch("/admin/edit_user/data", {
            method: "POST",
            body: JSON.stringify(database_json)
        });

        // EDITING USERS IS NOT IMPLEMENTED IN THE FILE SYSTEM

        location.href = "/admin";
    });
}