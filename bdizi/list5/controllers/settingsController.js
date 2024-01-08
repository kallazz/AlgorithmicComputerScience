import { getUserInfoByUserId, changeUserInfoJob, changeUserInfoAge } from "../databaseModels/UserInfo.js";

export const settings_get = async (req, res) => {
    const id = res.locals.user.id;
    const userInfo = await getUserInfoByUserId(id);
    res.render("userSettings", { userId: id, userInfo: userInfo });
};

export const settings_post = async (req, res) => {
    const { id, job, age } = req.body;
    if (job) {
        await changeUserInfoJob(id, job);
        const successMsg = "Job info changed";
        console.log(successMsg);
        res.status(200).json({ successMsg });
    }

    if (age) {
        await changeUserInfoAge(id, age);
        const successMsg = "Age info changed";
        console.log(successMsg);
        res.status(200).json({ successMsg });
    }
};