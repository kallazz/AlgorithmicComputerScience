import database from "../database.js";

export async function getUserInfoByUserId(id) {
    const [result] = await database.execute(
        "SELECT * FROM users_info WHERE user_id = ?",
        [id]
    );
    const userInfo = result[0];
    return userInfo;
};

export async function getUserInfoById(id) {
    const [result] = await database.execute(
        "SELECT * FROM users_info WHERE id = ?",
        [id]
    );
    const userInfo = result[0];
    return userInfo;
};

export async function createEmptyUserInfo(id) {
    let [result] = await database.execute(
        `
        INSERT INTO
        users_info (user_id, job, age)
        VALUES (?, NULL, NULL)
        `,
        [id]
    );

    const insertId = result.insertId;
    const newUserInfo = await getUserInfoById(insertId);
    return newUserInfo;
};

export async function changeUserInfoJob(id, newJob) {
    await database.execute(
        "UPDATE users_info SET job = ? WHERE user_id = ?",
        [newJob, id]
    );
}

export async function changeUserInfoAge(id, newAge) {
    await database.execute(
        "UPDATE users_info SET age = ? WHERE user_id = ?",
        [newAge, id]
    );
}