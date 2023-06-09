//

const COMPANY_NAME = "Guachis";

const MAP = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const getSalt = (length) => {
    let salt = '';

    for (let index = 0; index < length; index++) {
        const random_number = Math.floor(Math.random() * Hash.MAP.length);
        salt += Hash.MAP[random_number];
    }

    return salt;
}

const go_back_button = document.querySelector("#go_back_button");

go_back_button.addEventListener('click', () => {
    window.history.back();
});

// Add user

const user_send_button = document.querySelector("#user_send_button");

user_send_button.addEventListener('click', async () => {
    const user_id = document.querySelector("#user_id");
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
        phone_number: user_phone_number.value,
    };

    await fetch("/admin/add_user", {
        method: "POST",
        body: JSON.stringify(database_json)
    });
});


// });

// Remove user

// Edit user
